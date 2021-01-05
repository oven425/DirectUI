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
	case WM_MOUSEHOVER:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_MOUSEMOVE:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
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
		if (ww->m_MinHeight > 0)
		{
			int h = rc->bottom - rc->top;
			if (ww->m_MinHeight > h)
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
		float dpiscale = dpi / 96.0;
		ww->OnSize(width, height, dpiscale);
	}
	break;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

void CWindow::ReDraw()
{
	this->OnRender(this->pRT);
}

bool CWindow::Init(HWND hwnd)
{
	this->m_hWnd = hwnd;
	SetWindowSubclass(this->m_hWnd, WinProc, 0, (DWORD_PTR)this);

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	RECT rc;
	GetClientRect(hwnd, &rc);

	UINT dpi = ::GetDpiForWindow(this->m_hWnd);
	float dpiscale = dpi/96.0;
	float width = rc.right - rc.left;
	//width = width / dpiscale;
	float height = rc.bottom - rc.top;
	//height = height / dpiscale;
	//CDirectUI_Rect rc(0, 0, rc.right, rc.bottom);
	//rc = rc / dpiscale;
	// Create a Direct2D render target          
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hwnd,
			D2D1::SizeU((width/dpi, height/dpi))
		),
		&pRT
	);

	this->OnSize(width, height, dpiscale);
	return true;
}

void CWindow::OnSize(float width, float height, float dpiscale)
{
	this->pRT->Resize(D2D1::SizeU(width/ dpiscale, height/ dpiscale));
	CContentControl::OnSize(width, height, dpiscale);
	this->Measure(width / dpiscale, height / dpiscale, this->pRT);
	this->Arrange(0, 0, width / dpiscale, height / dpiscale);

}

void CWindow::OnRender(ID2D1RenderTarget* pRT)
{	
	this->pRT->BeginDraw();
	//this->pRT->Clear(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f));
	CContentControl::OnRender(this->pRT);

	this->pRT->EndDraw();


}

void CWindow::SetTitle(const wchar_t* data)
{
	::SetWindowTextW(this->m_hWnd, data);
}