#pragma once
#include <chrono>
using namespace std;

class Dispatch;

class DispatcherTimer
{
private:
	friend class Dispatch;
public:
	DispatcherTimer()
	{
		Dispatcher->AddTimer(*this);
	}

	~DispatcherTimer()
	{
		Dispatcher->RemoveTimer(*this);
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
	Dispatch* Dispatcher;
	void CheckTime()
	{

	}
	chrono::steady_clock::time_point m_CurrentTime;
};

