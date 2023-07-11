#pragma once
#include <functional>
#include <vector>
#include <map>
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
		auto ui = std::hash<std::function<T_Result(Args...)>>(data);
		//m_Funs1[data] = 1;
		return data;
	}

	void operator-=(std::function<T_Result(Args...)> data)
	{
		//int index = 0;
		//std::function<T_Result(Args...)> func = this->m_Funs[0];
		//auto hn = data.target_type();
		//auto t1 = func();
		//auto t2 = data.target();
		//auto bb = t1 == t2;
		//auto bb = func == data;
		//for (auto oo : this->m_Funs)
		//{
		//	if (oo == data)
		//	{
		//		index++;
		//		break;
		//	}
		//}
		//this->m_Funs.erase(this->m_Funs.begin()+index);

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
	map< std::function<T_Result(Args...)>, int> m_Funs1;
};

