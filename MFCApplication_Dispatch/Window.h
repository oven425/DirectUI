#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>

#include "ContentControl.h"
class Window : public ContentControl
{
public:
	static shared_ptr<Window> Attach();
protected:
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	int aa = 0;
};

