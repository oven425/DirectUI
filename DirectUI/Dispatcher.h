#pragma once
#include <functional>
using namespace std;
#include <Windows.h>
namespace DirectUI
{
	namespace Threading
	{
		class __declspec(dllexport) Dispatcher
		{
		public:
			Dispatcher();
			void Invoke(std::function<void()> data) { data(); }
		protected:
			HANDLE m_hTimerQueue = NULL;
			HANDLE m_hTimeUI = NULL;
			static void CALLBACK UITimer(PVOID lpParam, BOOLEAN TimerOrWaitFired);
		};

	}
}


