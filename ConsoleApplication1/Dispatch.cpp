#include "Dispatch.h"
Dispatch Dispatch::sInstance;

//void Dispatch::Look()
//{
//	//for (auto oo : this->m_Timers)
//	//{
//	//	oo->CheckTime();
//	//}
//
//}

void Dispatch::AddTimer(DispatcherTimer* data)
{
	
	this->m_Timers.push_back(data);
}

