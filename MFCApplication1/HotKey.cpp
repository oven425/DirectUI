#include "pch.h"
#include "HotKey.h"

HHOOK HotKey::m_hHook = NULL;
HotKey* HotKey::m_Instance = new HotKey();
LRESULT HotKey::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	auto kb = (KBDLLHOOKSTRUCT*)lParam;
	
	if (m_Instance->m_OnScancode != nullptr)
	{
		
		m_Instance->m_OnScancode(kb->scanCode);
	
	}
	auto find = m_Instance->m_Actions.find(kb->scanCode);
	if (find != m_Instance->m_Actions.end())
	{
		find->second();
	}
	return CallNextHookEx(m_hHook, nCode, wParam, lParam);
}

void HotKey::Start()
{
	if (m_hHook == NULL)
	{
		m_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	}
}

void HotKey::Stop()
{
	if (m_hHook != NULL)
	{
		::UnhookWindowsHookEx(m_hHook);
		m_hHook = NULL;
	}

}
