#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>

#include "ContentControl.h"
#include "MouseDevice.h"
class Window : public ContentControl
{
public:
	Window(HWND hwnd);
	~Window();
protected:
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	HWND m_hWnd;
	MouseDevice m_Mouse;
private:
	
};

