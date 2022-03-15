#pragma once
class MouseDevice
{
public:
	MouseDevice();
	LRESULT FilterMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
protected:
};

