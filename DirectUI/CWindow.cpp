#include "pch.h"
#include "CWindow.h"
using namespace DirectUI;
using	namespace Control;

LRESULT CWindow::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	CWindow* ww = (CWindow*)dwRefData;
	
	switch (uMsg)
	{
	case WM_ERASEBKGND:
	case WM_PAINT:
	{
		ww->OnRender();
		::OutputDebugStringA("WM_PAINT\r\n");
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
	return true;
}

void CWindow::OnSize(int width, int height)
{

}

void CWindow::OnRender()
{

}