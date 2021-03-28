#pragma once
#include <functional>
#include <thread>

namespace DirectUI
{
	class __declspec(dllexport) CTimer
	{
	public:
		void Start();
		void Stop();
		std::function<void()> TickHandler;
	protected:
		int m_Delay = 0;
		int m_Inerval = 0;
	};
}


