#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <chrono>
#include <queue>
#include <tuple>
#include <mutex>
using namespace std;

//#include "DispatcherTimer.h"


class DispatcherTimer;

class Dispatch
{
	struct data1
	{
		data1() {}
		data1(function<void()> action1, bool async)
		{
			action = action1;
			if (async == false)
			{
				lock = ::make_unique<mutex>();
				wait = ::make_unique<condition_variable>();
			}
		}
		function<void()> action;
		unique_ptr<mutex> lock;
		unique_ptr<condition_variable> wait;
	};
public:
	void Loop()
	{
		while (true)
		{
			if (m_Actions.empty() == false)
			{
				m_ActionsLock.lock();
				auto dd = &m_Actions.front();
				m_ActionsLock.unlock();

				m_Actions.front().action();
				
				if (dd->lock != nullptr)
				{
					dd->wait->notify_one();
				}
			}
			else if (this->m_Timers.empty() == false)
			{
				for (auto oo : this->m_Timers)
				{
					CheckTimer(oo);
				}
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
	}

	void Invoke(function<void()> action)
	{
		data1* dd;
		m_ActionsLock.lock();
		unique_ptr<data1> d = make_unique<data1>(action, false);
		m_Actions.push(data1(action, false));
		dd = &m_Actions.front();
		m_ActionsLock.unlock();

		std::unique_lock<std::mutex> lock(*dd->lock);
		dd->wait->wait(lock);
	}

	void InvokeAsync(function<void()> action)
	{
		m_ActionsLock.lock();
		m_Actions.push(data1(action, true));
		//m_Actions.push(action);
		m_ActionsLock.unlock();
	}
	static Dispatch& Instance()
	{
		return m_Instance;
	}
private:
	Dispatch()
	{
		thread tt(&Dispatch::Loop, this);
		tt.detach();
	}
	static Dispatch m_Instance;
	friend class DispatcherTimer;
	void AddTimer(DispatcherTimer* data)
	{
		this->m_Timers.push_back(data);
	}
	void RemoveTimer(const DispatcherTimer* data)
	{
		//this->m_Timers.erase(data);
	}
	void CheckTimer(DispatcherTimer* data);
	vector<DispatcherTimer*> m_Timers;
	queue<data1> m_Actions;
	mutex m_ActionsLock;
};



