#pragma once
#include <functional>
#include <mutex>
using namespace std;

template<typename T, typename = std::enable_if_t<std::is_class_v<T> || std::is_pointer_v<T>>>
class Lazy
{
public:
	Lazy(std::function<T()> createfunc)
		: m_CreateFunc(createfunc)
	{
	}
	Lazy(std::function<T()> createfunc, std::function<void(T obj)> destoryfunc)
		: m_CreateFunc(createfunc)
		, m_DestoryFunc(destoryfunc)
	{

	}

	~Lazy()
	{
		if (m_DestoryFunc != nullptr)
		{
			m_DestoryFunc(m_Data);
		}
	}
	T Value()
	{
		std::call_once(m_Once, [&]() {
			m_Data = m_CreateFunc();
			});
		return m_Data;
	}

private:
	std::function<T()> m_CreateFunc = nullptr;
	std::function<void(T obj)> m_DestoryFunc = nullptr;
	T m_Data = T{};
	once_flag m_Once;
};

