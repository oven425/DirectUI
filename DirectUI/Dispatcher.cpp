#include "pch.h"
#include "Dispatcher.h"
using namespace DirectUI;
using namespace Threading;

Dispatcher::Dispatcher()
{
	//this->m_hTimerQueue = ::CreateTimerQueue();
	//::CreateTimerQueueTimer(&this->m_hTimeUI, this->m_hTimerQueue, &Dispatcher::UITimer, this, 10000, 0, 0);

	this->m_Pool = thread(&Dispatcher::Polling, this);

}

void Dispatcher::Polling()
{

}

//void Dispatcher::UITimer(PVOID lpParam, BOOLEAN TimerOrWaitFired)
//{
//
//}