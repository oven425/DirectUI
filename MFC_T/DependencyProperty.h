#pragma once
#include <map>
#include <any>
using namespace std;

template<typename T>
class DependencyProperty
{
public:
	//static DependencyProperty<T> Register(CString name, T defaultvale)
	//{
	//	DependencyProperty<T> dp;
	//	auto hash = std::hash<string>(name);
	//	return dp;
	//}
	//friend void ChangePrivate( Point & );
	//friend void GetSaves(DependencyProperty<T>& dp);
private:
	T m_Value;
	int m_Hash;
	static map<std::size_t, void*> m_Saves;
};


//template <class T> class Test
//{
//private:
//	T val;
//public:
//	static int count;
//	Test()
//	{
//		count++;
//		count++;
//	}
//	// some other stuff in class
//};
//
//template<class T>
//int Test<T>::count = 0;

//class dpo;

template<typename T>
class dp
{
public:
	dp(const char* name)
	{
		//auto hash = std::hash<string>(name);
		size_t type = typeid(T).hash_code();
		m_Count++;

	}
	friend class dpo;
private:
	static int m_Count;
	T m_Value;
	int m_Hash;
	static map<std::size_t, dp<T>> m_dps;
};
template <typename T>
int dp<T>::m_Count = 10;
template <typename T>
map<std::size_t, dp<T>> dp<T>::m_dps;


class dpo
{
public:
	template<typename T> 
	friend class dp;

	template<typename T>
	void T(dp<T>& dp)
	{
		dp.m_aa = T{};
	}
private:
	int m_bb;
};

