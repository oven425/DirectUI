#pragma once
#include <chrono>
using namespace std;

#include "Dispatch.h"

class DispatcherTimer
{
private:
	friend class Dispatch;
public:
	DispatcherTimer()
	{
		//Dispatcher->AddTimer(*this);
		Dispatch::Instance().AddTimer(this);
	}

	~DispatcherTimer()
	{
		//Dispatcher->RemoveTimer(*this);
	}

	void Start()
	{
		this->m_CurrentTime = chrono::steady_clock::now();
	}

	void Stop()
	{
	}

private:
	bool m_IsEnable = false;
	void CheckTime(DispatcherTimer* data);
	chrono::steady_clock::time_point m_CurrentTime;
};

