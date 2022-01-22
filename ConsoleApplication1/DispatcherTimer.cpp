#include "DispatcherTimer.h"
void DispatcherTimer::CheckTime()
{

}

void Dispatch::Look()
{
	for (auto oo : this->m_Timers)
	{
		oo->CheckTime();
	}

}