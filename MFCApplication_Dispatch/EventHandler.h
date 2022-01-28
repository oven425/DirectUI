#pragma once
#include <set>
#include <functional>
using namespace std;

template <class TSender, class TArgs>
class EventHandler
{
public:
	std::function<void(TSender, TArgs)> m_F;
};

class EventArgs
{

};

//<template T>
//class EventHandler<T>
//{
//};

