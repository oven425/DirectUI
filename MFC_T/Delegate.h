#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template<typename ... Args>
class Action
{
public:
	void Invoke(Args... args)
	{
		m_Fun(args);
	}
private:
	std::function<void(Args...)> m_Fun;
};

template<typename T_Result, typename ... Args>
class Func
{
public:
	T_Result Invoke(Args... args)
	{
		return m_Fun(args);
	}
private:
	std::function<T_Result(Args...)> m_Fun;
};

//template<class T>
//class DelegateT
//{
//
//};


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

	//operator void(Args... args)
	//{

	//}

	//int operator()(Args... args)
	//{
	//	return 0;
	//}

	//int operator()() {
	//	return 5;
	//}

	//template<typename T>
	//inline typename std::enable_if<std::is_floating_point<T>::value, T>::type
	// operator()(Args... args)
	//{

	//}

	//template<typename T>
	//inline typename std::enable_if<!std::is_same<T, void>::value, T>::type
	//	operator()(Args... args)
	//{
	//	T_Result result = T_Result{};

	//	return result;
	//}


	template<typename T>
	inline typename std::enable_if<std::is_class<T>::value && !std::is_same<T, string>::value, T>::type
		TT(Args... args)
	{
		return "";
	}

	template<typename T>
	inline typename std::enable_if<std::is_arithmetic<T>::value, T>::type
		TT(Args... args)
	{
		return 0;
	}


	//T_Result operator()(Args... args)
	//{
	//	T_Result d;
	//	return d;
	//}


	//https://leimao.github.io/blog/CPP-Enable-If/
	//template <typename T_Result,
	//	typename std::enable_if<!std::is_void<T_Result>::value, bool>::type =
	//	true>

	//T_Result TT(Args... args)
	//{
	//	T_Result hr = T_Result{};
	//	for (auto oo : this->m_Funs)
	//	{
	//		hr = oo(args...);
	//	}
	//	return hr;
	//}

	//typename std::enable_if<std::is_void<T_Result>::value, void>
	//	TT1(Args... args)
	//{
	//	//T_Result hr = T_Result{};
	//	for (auto oo : this->m_Funs)
	//	{
	//		oo(args...);
	//	}
	//	//return "";
	//	//return hr;
	//}


	//template <typename T,
	//	std::enable_if_t<!std::is_void<T_Result>::value, bool> =
	//	true> // It does not matter what type it is and what the value is,
	//T_Result operator()(Args... args)
	//{
	//	T_Result hr = T_Result{};
	//	for (auto oo : this->m_Funs)
	//	{
	//		hr = oo(args...);
	//	}
	//	//return "";
	//	return hr;
	//}

	//template <typename T,
	//	std::enable_if_t<std::is_void<T_Result>::value, bool> =
	//	true> // It does not matter what type it is and what the value is,
	//void operator()(Args... args)
	//{
	//	for (auto oo : this->m_Funs)
	//	{
	//		oo(args...);
	//	}
	//}


	//template <typename T,
	//	std::enable_if_t<std::is_void<T_Result>::value, bool> =
	//	true> // It does not matter what type it is and what the value is,
	//// as long as the value is of the type.
	//void barTT()
	//{
	//	std::cout << "T is int" << std::endl;
	//}

	//template <typename T,
	//	std::enable_if_t<std::is_void<T_Result>::value, bool> =
	//	false> // It does not matter what type it is and what the value is,
	//// as long as the value is of the type.
	//void barTT()
	//{
	//	std::cout << "T is int" << std::endl;
	//}



	//template <typename T,
	//	std::enable_if_t<std::is_integral<T>::value, bool> =
	//	true> // It does not matter what type it is and what the value is,
	//// as long as the value is of the type.
	//void bar()
	//{
	//	std::cout << "T is int" << std::endl;
	//}

	//template <typename T,
	//	std::enable_if_t<std::is_floating_point<T>::value, bool> =
	//	true> // It does not matter what type it is and what the value is,
	//// as long as the value is of the type.
	//void bar()
	//{
	//	std::cout << "T is float" << std::endl;
	//}

	//template <typename T,
	//	std::enable_if_t<std::is_array<T>::value, bool> =
	//	true> // It does not matter what type it is and what the value is,
	//// as long as the value is of the type.
	//void bar()
	//{
	//	std::cout << "T is float" << std::endl;
	//}
public:
	vector<std::function<T_Result(Args...)>> m_Funs;
};

