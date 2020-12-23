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
		ww->OnRender();
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
	return true;
}

void CWindow::OnSize(int width, int height)
{
	RECT rc;
	GetClientRect(this->m_hWNd, &rc);
	this->pRT->Resize(D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));
	//this->m_Children->OnSize(width, height);
}

void CWindow::OnRender()
{
	//this->m_Children->OnRender(this->pRT);
	RECT rc;
	GetClientRect(this->m_hWNd, &rc);
	this->Background->Refresh(pRT);
	ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();

	//HRESULT hr = pRT->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::Purple, 1.0f),
	//	&m_pBlackBrush
	//);

	D2D1_RECT_F size = { 0 };
	size.bottom = rc.bottom;
	size.left = rc.left;
	size.right = rc.right;
	size.top = rc.top;
	this->pRT->BeginDraw();
	this->pRT->FillRectangle(size, m_pBlackBrush);
	this->pRT->EndDraw();
	//m_pBlackBrush->Release();

}