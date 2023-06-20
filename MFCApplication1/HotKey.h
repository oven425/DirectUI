#pragma once
#include <Windows.h>

#include <functional>
#include <map>
using namespace std;

class HotKey
{
public:
	static HotKey& Cpauture()
	{
		return *m_Instance;
	}
	
	void Start();
	void Stop();
	void UseScanCode(int scancode, function<void()> action)
	{
		m_Actions[scancode] = action;
	}
	void SetScanCodeEvent(function<void(int scancode)> action)
	{
		m_OnScancode = action;
	}
	
protected:
	function<void(int scancode)> m_OnScancode;
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static HHOOK m_hHook;
	static HotKey* m_Instance;
	map<int, function<void()>> m_Actions;
private:
	HotKey() {};
};

