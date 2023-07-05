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

template<typename T>
class dp
{
public:
	friend class dpo;
	static int doit();
private:
	T m_Value = T{};
	static int m_pp;
	static map<int, int> m_Saves;
};


class dpo
{
public:
	template<typename T>
	friend int dp<T>::doit()
	{
		return dp<T>::m_pp;
	}
	template<typename T>
	void AA(dp<T> dp)
	{
		dp.m_Value;
		
	}
};

