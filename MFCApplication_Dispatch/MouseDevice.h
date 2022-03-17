#pragma once
class MouseDevice
{
public:
	MouseDevice(HWND hwnd);
	LRESULT FilterMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
protected:
	void Record(WPARAM wParam, LPARAM lParam);
	bool m_IsRecord = false;
	POINT m_LastPt = { 0 };
	HWND m_hWnd;
};

