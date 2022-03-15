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
MouseDevice::MouseDevice()
{

}

LRESULT MouseDevice::FilterMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_MOUSEMOVE:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
	}
	break;
	}
	return 0;
}