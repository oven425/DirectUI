#include "pch.h"
#include "CWindow.h"


LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	CWindow* ww = (CWindow*)dwRefData;
	switch (uMsg)
	{
	case WM_PAINT:
	{
		::OutputDebugStringA("WM_PAINT\r\n");
	}
	break;
	case WM_SIZE:
	{
		::OutputDebugStringA("WM_SIZE\r\n");
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