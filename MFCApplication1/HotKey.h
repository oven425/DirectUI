#pragma once
#include <Windows.h>

#include <functional>
using namespace std;

class HotKey
{
public:
	function<void(int scancode)> m_OnScancode;
	void Capture();
	
private:
	
};

