#pragma once
#include <functional>
#include <string>
using namespace std;


class CTT_Object;

template<class T>
struct CTTChangeArgs
{
	T OldValue;
	T NewValue;
};

class CTT_PropoertyBase
{
public:
	string Name;
};

template<class T>
class CTT_Propoerty:public CTT_PropoertyBase
{
public:
	std::function<void(const CTT_Object& sender, const CTTChangeArgs<T>& args)> Handler;
	CTTChangeArgs<T> Create()
	{
		return CTTChangeArgs<T>();
	}
};

