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
		for (auto oo : this->m_Funcs)
		{
			oo(obj, args);
		}
	}

	void operator+=(function<void(TSender, TArgs)> evt)
	{
		this->m_Funcs.push_back(evt);
	}
protected:
	vector<function<void(TSender, TArgs)>> m_Funcs;
};

class EventArgs
{
public:
	bool Canceled;
};

