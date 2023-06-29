#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;




template<class T_Result, class ... Args>
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

	//template<typename T=T_Result>
	//inline typename std::enable_if<std::is_void<T>::value, T>::type
	// FF(Args... args)
	//{

	//}

	//template<typename T = T_Result>
	//inline typename std::enable_if<!std::is_void<T>::value, T>::type
	//	FF(Args... args)
	//{
	//	return T{};
	//}


	template<typename T = T_Result>
	inline typename std::enable_if<std::is_void<T>::value, T>::type
		operator()(Args... args)
	{

	}

	template<typename T = T_Result>
	inline typename std::enable_if<!std::is_void<T>::value, T>::type
		operator()(Args... args)
	{
		return T{};
	}




public:
	vector<std::function<T_Result(Args...)>> m_Funs;
};

