#include "pch.h"
#include "Window.h"
LRESULT Window::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (uMsg)
	{
	case WM_PAINT:
	case WM_ERASEBKGND:
	{

	}
	break;
	case WM_LBUTTONDOWN:
	{

	}
	break;
	case WM_LBUTTONUP:
	{

	}
	break;
	case WM_MOUSEMOVE:
	{

	}
	break;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

shared_ptr<Window> Window::Attach()
{
	auto window = make_shared<Window>();
	window->aa = 100;
	return window;
}