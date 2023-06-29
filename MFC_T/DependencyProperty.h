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
private:
	T m_Value;
	int m_Hash;
	static map<std::size_t, void*> m_Saves;
};

