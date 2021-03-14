#include "pch.h"
#include "CWindow.h"
using namespace DirectUI;
using namespace Control;

LRESULT CWindow::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	CWindow* ww = (CWindow*)dwRefData;
	
	switch (uMsg)
	{
	case WM_ERASEBKGND:
	case WM_PAINT:
	{
		ww->ReDraw();
	}
	break;
	case WM_MOUSELEAVE:
	case WM_MOUSEMOVE:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		//char msg[256] = { 0 };
		//::sprintf_s(msg, "mouse move x:%d y%d\r\n", xPos, yPos);
		//::OutputDebugStringA(msg);
		if (uMsg == WM_MOUSELEAVE)
		{
			ww->m_TrackMouse = false;
		}
		else if (ww->m_TrackMouse == false)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.hwndTrack = ww->m_hWnd;
			tme.dwHoverTime = 100;
			BOOL bb = ::TrackMouseEvent(&tme);
			ww->m_TrackMouse == true;
		}
		vector<shared_ptr<CControl>> childs;
		if (ww->HitTest(xPos, yPos, childs) == true)
		{
			MouseMoveArgs mouseargs = { 0 };
			mouseargs.X = xPos;
			mouseargs.Y = yPos;
			for (auto oo : childs)
			{
				oo->OnMouseMove(mouseargs);
				if (oo->MouseMoveHandler)
				{
					oo->MouseMoveHandler(oo, mouseargs);
				}
			}
			if (!ww->m_MouseStorage.mouseon)
			{
				ww->m_MouseStorage.mouseon = childs.back();
				ww->m_MouseStorage.mouseon->OnMouseEnter(mouseargs);
				if (ww->m_MouseStorage.mouseon->MouseEnterHandler)
				{
					ww->m_MouseStorage.mouseon->MouseEnterHandler(ww->m_MouseStorage.mouseon, mouseargs);
				}
			}
			else if (ww->m_MouseStorage.mouseon && ww->m_MouseStorage.mouseon != childs.back())
			{
				ww->m_MouseStorage.mouseon->OnMouseLeave(mouseargs);
				if (ww->m_MouseStorage.mouseon->MouseLeaveHandler)
				{
					ww->m_MouseStorage.mouseon->MouseLeaveHandler(ww->m_MouseStorage.mouseon, mouseargs);
				}
				ww->m_MouseStorage.mouseon = childs.back();
				ww->m_MouseStorage.mouseon->OnMouseEnter(mouseargs);
				if (ww->m_MouseStorage.mouseon->MouseEnterHandler)
				{
					ww->m_MouseStorage.mouseon->MouseEnterHandler(ww->m_MouseStorage.mouseon, mouseargs);
				}
			}
		}
		ww->ReDraw();
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		::SetCapture(ww->m_hWnd);
		vector<shared_ptr<CControl>> childs;
		if (ww->HitTest(xPos, yPos, childs) == true)
		{
			MouseLeftButtonDownArgs mouseargs = { 0 };
			mouseargs.X = xPos;
			mouseargs.Y = yPos;
			ww->m_MouseStorage.leftbutton = childs.back();
			for (auto oo : childs)
			{
				oo->OnMouseLeftButtonDown(mouseargs);
				if (oo->MouseLeftButtonDownHandler)
				{
					oo->MouseLeftButtonDownHandler(oo, mouseargs);
				}
			}
		}
		ww->ReDraw();
	}
	break;
	case WM_LBUTTONUP:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		vector<shared_ptr<CControl>> childs;
		if (ww->HitTest(xPos, yPos, childs) == true)
		{
			MouseLeftButtonUpArgs mouseargs = { 0 };
			mouseargs.X = xPos;
			mouseargs.Y = yPos;
			for (auto oo : childs)
			{
				oo->OnMouseLeftButtonUp(mouseargs);
				if (oo->MouseLeftButtonUpHandler)
				{
					oo->MouseLeftButtonUpHandler(oo, mouseargs);
				}
			}
			if (ww->m_MouseStorage.leftbutton && ww->m_MouseStorage.leftbutton == childs.back())
			{
				if (childs.back()->MouseClickHandler)
				{
					childs.back()->MouseClickHandler(childs.back(), MouseClickArgs());
				}
			}
		}
		ww->m_MouseStorage.leftbutton = nullptr;
		::ReleaseCapture();
	}
	break;
	case WM_SIZING:
	{
		RECT* rc = (RECT*)lParam;
		if (ww->m_MinWidth > 0)
		{
			int w = rc->right - rc->left;
			if (ww->m_MinWidth > w)
			{
				rc->right = rc->left + ww->m_MinWidth;
			}
		}
		if (ww->m_MaxWidth > 0)
		{
			int w = rc->right - rc->left;
			if (ww->m_MaxWidth < w)
			{
				rc->right = rc->left + ww->m_MaxWidth;
			}
		}
		if (ww->m_MinHeight > 0)
		{
			int h = rc->bottom - rc->top;
			if (ww->m_MinHeight > h)
			{
				rc->bottom = rc->top + ww->m_MinHeight;
			}
		}
		if (ww->m_MaxHeight > 0)
		{
			int h = rc->bottom - rc->top;
			if (ww->m_MinHeight < h)
			{
				rc->bottom = rc->top + ww->m_MinHeight;
			}
		}
	}
	break;
	
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		UINT dpi = ::GetDpiForWindow(hWnd);
		//dpi = 96;
		float dpiscale = (float)(dpi / 96.0);
		ww->OnSize(width, height, dpiscale);
		
	}
	break;
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;
		UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
		DragFilesArgs dragfiles;
		for (int i = 0; i < nFiles; i++)
		{
			wchar_t szFileName[MAX_PATH + 1] = { 0 };
			DragQueryFile(hDrop, i, szFileName, MAX_PATH);
			dragfiles.files.push_back(szFileName);
			::OutputDebugStringW(szFileName);
		}
		::DragFinish(hDrop);
		if (ww->DragHandler)
		{
			ww->DragHandler(ww->shared_from_this(), dragfiles);
		}
	}
	break;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

void CWindow::ReDraw()
{
	this->OnRender(this->pRT, true);
}

bool CWindow::Init(HWND hwnd)
{
	this->m_hWnd = hwnd;
	

	SetWindowSubclass(this->m_hWnd, WinProc, 0, (DWORD_PTR)this);

	

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	RECT rc;
	GetClientRect(hwnd, &rc);

	
	float width = (float)(rc.right - rc.left);
	//width = width / dpiscale;
	float height = (float)(rc.bottom - rc.top);

	hr = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hwnd,
			D2D1::SizeU((width, height))
		),
		&pRT
	);

	UINT dpi = ::GetDpiForWindow(this->m_hWnd);
	//dpi = 96;
	float dpiscale = (float)(dpi / 96.0);
	this->OnSize(width, height, dpiscale);
	return true;
}

bool CWindow::HitTest(int x, int y, vector<shared_ptr<CControl>>& childs)
{
	float x_dpi = x / this->m_DpiScale;
	float y_dpi = y / this->m_DpiScale;
	return ::CContentControl::HitTest(x_dpi, y_dpi, childs);
}

void CWindow::OnSize(float width, float height, float dpiscale)
{
	this->pRT->Resize(D2D1::SizeU(width, height));
	CContentControl::OnSize(width, height, dpiscale);

	this->Measure(CDirectUI_Size(width / dpiscale, height / dpiscale), this->pRT);
	this->Arrange(0, 0, width / dpiscale, height / dpiscale);
}


void CWindow::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{	
	this->pRT->BeginDraw();
	this->pRT->Clear(D2D1::ColorF(D2D1::ColorF::Black, 1.0f));
	
	CContentControl::OnRender(this->pRT, calculate_dpi);

	this->pRT->EndDraw();
}

void CWindow::SetTitle(const wchar_t* data)
{
	::SetWindowTextW(this->m_hWnd, data);
}

void CWindow::SetAllowDropFiles(bool data)
{
	DragAcceptFiles(this->m_hWnd, data==true?TRUE:FALSE);
}