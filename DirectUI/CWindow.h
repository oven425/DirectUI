#pragma once
#include <Windows.h>
#include <commctrl.h>
class __declspec(dllexport) CWindow
{
public:
	bool Init(HWND hwnd);
protected:
	HWND m_hWNd = NULL;
};

