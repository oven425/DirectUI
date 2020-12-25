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
		//ww->OnRender(ww->pRT);
		//::OutputDebugStringA("WM_PAINT\r\n");
	}
	break;
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		ww->OnSize(width, height);
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
	this->m_hWNd = hwnd;
	SetWindowSubclass(this->m_hWNd, WinProc, 0, (DWORD_PTR)this);

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	RECT rc;
	GetClientRect(hwnd, &rc);

	// Create a Direct2D render target          
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hwnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
		),
		&pRT
	);
	this->OnSize(rc.right - rc.left, rc.bottom - rc.top);
	return true;
}

void CWindow::OnSize(int width, int height)
{
	this->pRT->Resize(D2D1::SizeU(width, height));
	CContentControl::OnSize(width, height);

}

void CWindow::OnRender(ID2D1HwndRenderTarget* pRT)
{	
	this->pRT->BeginDraw();

	CContentControl::OnRender(this->pRT);

	this->pRT->EndDraw();


}