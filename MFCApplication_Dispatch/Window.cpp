#include "pch.h"
#include "Window.h"
LRESULT Window::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	Window* aa = (Window*)dwRefData;
	if (aa->m_Mouse != nullptr)
	{
		aa->m_Mouse->FilterMessage(hWnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
	}
	
	//switch (uMsg)
	//{
	//case WM_PAINT:
	//case WM_ERASEBKGND:
	//{

	//}
	//break;
	//case WM_LBUTTONDOWN:
	//{
	//	::OutputDebugStringA("WM_LBUTTONDOWN\r\n");
	//}
	//break;
	//case WM_LBUTTONUP:
	//{

	//}
	//break;
	//case WM_MBUTTONDOWN:
	//{

	//}
	//break;
	//case WM_MBUTTONUP:
	//{

	//}
	//break;
	//case WM_RBUTTONDOWN:
	//{

	//}
	//break;
	//case WM_RBUTTONUP:
	//{

	//}
	//break;
	//case WM_MOUSEMOVE:
	//{
	//	::OutputDebugStringA("WM_MOUSEMOVE\r\n");
	//}
	//break;
	//}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

Window::Window(HWND hwnd)
	: m_hWnd(hwnd)
{
	this->m_Mouse = ::make_unique<MouseDevice>(hwnd);
	::SetWindowSubclass(this->m_hWnd, WinProc, 0, (DWORD_PTR)this);
	
}

Window::~Window()
{
	RemoveWindowSubclass(this->m_hWnd, WinProc, (DWORD_PTR)this);
}