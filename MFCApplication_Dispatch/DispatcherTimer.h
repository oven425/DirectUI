#pragma once
#include <chrono>
using namespace std;

#include "Dispatch.h"
#include "EventHandler.h"

class DispatcherTimer
{
private:
	friend class Dispatch;
public:
	DispatcherTimer()
	{
		Dispatch::Instance().AddTimer(this);
	}

	~DispatcherTimer()
	{
		Dispatch::Instance().RemoveTimer(this);
	}

	void Start();

	void Stop();
	chrono::milliseconds m_TimeSpan;
	EventHandler<DispatcherTimer, EventArgs> Tick;
private:
	bool m_IsEnable = false;
	chrono::steady_clock::time_point m_CurrentTime;
	//chrono::steady_clock::duration<> m_Interval;
};

