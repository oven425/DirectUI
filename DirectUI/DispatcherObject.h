#pragma once
#include <memory>
using namespace std;

#include "Dispatcher.h"

namespace DirectUI
{
	namespace Threading
	{
		class DispatcherObject
		{
		public:
			DispatcherObject();
			Dispatcher& GetDispatcher() ;
			__declspec(property(get = GetDispatcher)) const Dispatcher& Dispatch;
		private:
			static shared_ptr<Dispatcher> m_Dispatcher;
		};
	}
}


