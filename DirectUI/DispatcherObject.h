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
			const Dispatcher& GetDispatcher() { return *this->m_Dispatcher; }
			__declspec(property(get = GetBackground)) const Dispatcher& Dispatch;
		private:
			static shared_ptr<Dispatcher> m_Dispatcher;
		};
	}
}


