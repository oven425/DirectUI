#pragma once
#include <set>
#include <vector>
#include <functional>
using namespace std;

//template <class TArgs>
//class EventHandler
//{
//public:
//	std::function<void(void*, TArgs)> m_F;
//};

template <class TSender, class TArgs>
class EventHandler
{

public:
	void Fire(TSender obj, TArgs args)
	{
		for (auto oo : this->m_Fs)
		{
			oo(obj, args);
		}
	}

	void operator+=(function<void(TSender, TArgs)> evt)
	{
		this->m_Fs.push_back(evt);
	}

	vector<function<void(TSender, TArgs)>> m_Fs;
	std::function<void(TSender, TArgs)> m_F;
};

class EventArgs
{
public:
	bool Canceled;
};

//<template T>
//class EventHandler<T>
//{
//};

