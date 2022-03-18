#include "pch.h"
#include "MouseDevice.h"
//HwndSource -FilterMessage->
//HwndMouseInputProvider -ReportInput ->
//InputProviderSite -ReportInput->
//InputManager -ProcessInput->ProcessStagingArea->
//MouseDevice -> PreProcessInput-> InputManager
//MouseDevice -> PreNotifyInput -> InputManager
//MouseDevice -> PostProcessInput -> 


//MouseDevice PreNotifyInput get mouse move tagert element
MouseDevice::MouseDevice(HWND hwnd)
	: m_hWnd(hwnd)
{

}

LRESULT MouseDevice::FilterMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		this->Record(wParam, lParam);
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (this->m_IsRecord == false)
		{
			this->m_IsRecord = true;
			TRACKMOUSEEVENT te = { 0 };
			te.hwndTrack = this->m_hWnd;
			te.dwHoverTime = 100;
			te.cbSize = sizeof(TRACKMOUSEEVENT);
			te.dwFlags = TME_HOVER | TME_LEAVE;
			BOOL bb = TrackMouseEvent(&te);
		}
		this->Record(wParam, lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		this->Record(wParam, lParam);
	}
	break;
	case WM_MOUSELEAVE:
	{
		::OutputDebugStringA("WM_MOUSELEAVE\r\n");
		this->m_IsRecord = false;
	}
	break;
	case WM_MOUSEHOVER:
	{
		::OutputDebugStringA("WM_MOUSEHOVER\r\n");
	}
	break;
	}
	return 0;
}

void MouseDevice::Capture(UIElement* data)
{

}

void MouseDevice::Record(WPARAM wParam, LPARAM lParam)
{
	if (this->m_IsRecord == true)
	{
		this->m_LastPt.x = GET_X_LPARAM(lParam);
		this->m_LastPt.y = GET_Y_LPARAM(lParam);
	}
}