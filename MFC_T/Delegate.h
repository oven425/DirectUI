#pragma once
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T_Result, typename ... Args>
class Delegate
{
public:
	std::function<T_Result(Args...)> operator+=(std::function<T_Result(Args...)> data)
	{
		this->m_Funs.push_back(data);
		return data;
	}

	void operator-=(std::function<T_Result(Args...)> data)
	{
		int index = 0;
		for (auto oo : this->m_Funs)
		{
			if (oo == data)
			{
				index++;
				break;
			}
		}
		this->m_Funs.erase(this->m_Funs.begin()+index);

	}

	T_Result operator()(Args... args)
	{
		T_Result hr = T_Result{};
		for (auto oo : this->m_Funs)
		{
			hr = oo(args...);
		}
		//return "";
		return hr;
	}

	//inline typename  std::enable_if<std::is_void<T_Result>>>::type
	//void operator()(Args... args)
	//{
	//	//T_Result hr = T_Result{};
	//	for (auto oo : this->m_Funs)
	//	{
	//		oo(args...);
	//	}
	//	//return "";
	//	//return hr;
	//}

public:
	vector<std::function<T_Result(Args...)>> m_Funs;
};

