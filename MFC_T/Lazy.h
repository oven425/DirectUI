#pragma once
#include <functional>
#include <mutex>
using namespace std;

template <class T>
class Lazy
{
public:
	Lazy(std::function<void()> action)
	{

	}
	T Value()
	{
		return m_Data;
	}
	T m_Data;
	once_flag m_Once;
};

