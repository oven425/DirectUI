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
		UINT dpi = ::GetDpiForWindow(hWnd);
		double dpiscale = dpi / 96.0;
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
	double dpiscale = dpi/96.0;
	double width = rc.right - rc.left;
	//width = width / dpiscale;
	double height = rc.bottom - rc.top;
	//height = height / dpiscale;

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

void CWindow::OnSize(double width, double height, double dpiscale)
{
	this->pRT->Resize(D2D1::SizeU(width/ dpiscale, height/ dpiscale));
	CContentControl::OnSize(width/ dpiscale, height/ dpiscale, dpiscale);
	this->Arrange(0, 0, width, height);

}

void CWindow::OnRender(ID2D1HwndRenderTarget* pRT)
{	
	this->pRT->BeginDraw();
	//this->pRT->Clear(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f));
	CContentControl::OnRender(this->pRT);

	this->pRT->EndDraw();


}