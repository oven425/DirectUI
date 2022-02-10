#include "pch.h"
#include "DispatcherTimer.h"


void DispatcherTimer::Start()
{
	this->m_CurrentTime = chrono::steady_clock::now();
	this->m_IsEnable = true;
}

void DispatcherTimer::Stop()
{
	this->m_IsEnable = false;
}

void Dispatch::CheckTimer(DispatcherTimer* data)
{
	if (data->m_IsEnable == true)
	{
		auto now = chrono::steady_clock::now();
		std::chrono::nanoseconds s = now - data->m_CurrentTime;
		//chrono::microseconds ms = data->m_TimeSpan - s;
		if (s > data->m_TimeSpan)
		{
			data->m_CurrentTime = now;
			data->Tick.Fire(*data, EventArgs());
		}
	}
}