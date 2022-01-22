#pragma once
#include <vector>
using namespace std;


//#include "DispatcherTimer.h"
class DispatcherTimer;
class Dispatch
{
private:
	friend class DispatcherTimer;
public:
	void Look();
	//{
	//	for (auto oo : this->m_Timers)
	//	{
	//		oo->CheckTime();
	//	}
	//}
	
	static Dispatch& getInstance() {
		return sInstance;
	}
private:
	Dispatch()
	{

	}
	static Dispatch sInstance;
	void AddTimer(DispatcherTimer* data);
	vector<DispatcherTimer*> m_Timers;
};


