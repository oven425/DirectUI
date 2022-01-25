#pragma once
#include <set>
#include <functional>
using namespace std;

template <class T>
class EventHandler
{
public:
	std::function<void(T)> m_F;
};

class EventArgs
{

};

//<template T>
//class EventHandler<T>
//{
//};

