#pragma once
#include <functional>
#include <queue>
#include <thread>
using namespace std;
#include <Windows.h>
namespace DirectUI
{
	namespace Threading
	{
		class __declspec(dllexport) Dispatcher final
		{
		public:
			Dispatcher();
			void Invoke(std::function<void()> data) { data(); }
		protected:
			thread m_Pool;
			void Polling();
			//HANDLE m_hTimerQueue = NULL;
			//HANDLE m_hTimeUI = NULL;
			//static void CALLBACK UITimer(PVOID lpParam, BOOLEAN TimerOrWaitFired);
		};

	}
}


