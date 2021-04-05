#include "pch.h"
#include "DispatcherObject.h"
using namespace DirectUI;
using namespace Threading;
shared_ptr<Dispatcher> DispatcherObject::m_Dispatcher;

DispatcherObject::DispatcherObject()
{
	if (!m_Dispatcher)
	{
		m_Dispatcher = ::make_shared<Dispatcher>();
	}
}