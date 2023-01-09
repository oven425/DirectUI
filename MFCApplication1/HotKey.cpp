#include "pch.h"
#include "HotKey.h"

HHOOK m_hHook = NULL;
HotKey* m_Instance = NULL;
static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (m_Instance->m_OnScancode != nullptr)
	{
		auto kb = (KBDLLHOOKSTRUCT*)lParam;
		m_Instance->m_OnScancode(kb->scanCode);
	}
	return CallNextHookEx(m_hHook, nCode, wParam, lParam);
}

void HotKey::Capture()
{
	m_Instance = this;
	m_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
}