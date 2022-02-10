#include "Dispatch.h"
Dispatch Dispatch::sInstance;



void Dispatch::AddTimer(DispatcherTimer* data)
{
	
	this->m_Timers.push_back(data);
}

