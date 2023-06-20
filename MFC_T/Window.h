#pragma once
#include <atlstr.h>




class Window
{
public:
	static Window* Mount(HWND hwnd)
	{
		auto window = new Window(hwnd);
		
		return window;
	}
private:
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto window = (Window*)dwRefData;
		switch (uMsg)
		{
		case WM_SIZE:
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);
			window->OnSize(width, height);
		}
		break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	void OnSize(UINT width, UINT height)
	{
		CString str;
		str.Format(_T("width:%d height:%d\r\n"), width, height);
		::OutputDebugString(str);
	}

	Window(HWND hwnd)
		: m_hWnd(hwnd)
	{
		SetWindowSubclass(this->m_hWnd, WinProc, 0, (DWORD_PTR)this);
	}

	
	HWND m_hWnd = NULL;
};



