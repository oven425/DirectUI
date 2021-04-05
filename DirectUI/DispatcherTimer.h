#pragma once
#include <functional>
#include <thread>

#include "DispatcherObject.h"

namespace DirectUI
{
	namespace Threading
	{
		class __declspec(dllexport) DispatcherTimer : public DispatcherObject
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
}


