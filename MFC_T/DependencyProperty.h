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

class dpo;

template<typename T>
class dp
{
public:
	dp()
	{
		m_aa++;
		m_Count++;
	}
	friend class dpo;

private:
	static int m_Count;
	T m_aa;
};


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

