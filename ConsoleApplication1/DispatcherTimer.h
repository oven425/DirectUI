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
		Dispatch::getInstance().AddTimer(this);
	}
	~DispatcherTimer()
	{

	}
	void Start()
	{
		this->m_CurrentTime = chrono::steady_clock::now();
	}

	void Stop()
	{
	}



private:
	//Dispatch* m_Dispatch;
	void CheckTime();
	chrono::steady_clock::time_point m_CurrentTime;
};
