#pragma once
#include <Windows.h>
class KeyBoard
{
public:
	//Keyboard.IsKeyDown -> KeyboardDevice.IsKeyDown -IsKeyDown_private()->
	//Win32KeyboardDevice.GetKeyStatesFromSystem
	static bool IsKeyDown(int key)
	{
		auto hr = ::GetKeyState(key);
		VK_TAB;
	}
};

