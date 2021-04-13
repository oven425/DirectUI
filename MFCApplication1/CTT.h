#pragma once
#include <memory>
#include <variant>
#include <functional>
#include <map>
using namespace std;

#include "CTT_Propoerty.h"

template<class T>
struct is_std_function : std::false_type {};

template<class T>
struct is_std_function<std::function<T>> : std::true_type {};

// the partial specialization of A is enabled via a template parameter
template<class T, class Enable = void>
class A {}; // primary template

template<class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
}; // specialization for floating point types


template<class T, class Enable = void>
class Event {}; // primary template
template<class T>
class Event<T, typename std::enable_if<is_std_function<T>::value>::type>
{
public:
	void operator+=(const T& data) 
	{

		this->m_Handlers.push_back(data);
	}

	void Fire(int data) 
	{
		for (auto oo : this->m_Handlers)
		{
			oo(data);
		}
	}
protected:
	vector<T> m_Handlers;
};



class CValueConvertBase
{

};

class CBindingBase
{

};

template<typename T>
class CBinding :CBindingBase
{
public:
	CValueConvertBase Convert;
};

class CTT_Object :public enable_shared_from_this<CTT_Object>
{
public:
	template<typename T>
	void SetValue(shared_ptr<CTT_Propoerty<T>> dp, shared_ptr<T> data)
	{
		shared_ptr<void> old;
		bool hasold = false;
		auto find = this->test.find(dp);
		if (find != this->test.end())
		{
			try
			{
				old = std::get<weak_ptr<void>>(find->second).lock();
				if (old)
				{
					hasold = true;
				}
			}
			catch (const std::bad_variant_access&)
			{
			}
		}

		if (hasold == true && data != old)
		{
			auto args = dp->Create();
			args.OldValue = *static_pointer_cast<T>(old);
			args.NewValue = *static_pointer_cast<T>(data);
			if (dp->Handler)
			{
				dp->Handler(*this, args);
			}
		}
		test[dp] = data;
	}

	template<typename T>
	void SetValue(shared_ptr<CTT_Propoerty<T>> dp, int data)
	{
		int old;
		bool hasold = false;
		auto find = this->test.find(dp);
		if (find != this->test.end())
		{
			try
			{
				old = std::get<int>(find->second);
				hasold = true;
			}
			catch (const std::bad_variant_access&)
			{
			}
		}

		if (hasold == true && data != old)
		{
			auto args = dp->Create();
			args.OldValue = old;
			args.NewValue = data;
			if (dp->Handler)
			{
				dp->Handler(*this, args);
			}
		}
		test[dp] = data;
	}
	//void SetValue(shared_ptr<CTT_Propoerty> dp, float data);
	//void SetValue(shared_ptr<CTT_Propoerty> dp, double data);

	template<typename T, typename T1>
	T GetValue(shared_ptr<CTT_Propoerty<T1>> dp)
	{
		auto find = this->test.find(dp);
		if (find != this->test.end())
		{
			try
			{
				auto aa = std::get<T>(find->second).lock();
				if (aa)
				{
					return aa;
				}
				//return std::get<T>(find->second);
			}
			catch (const std::bad_variant_access&)
			{
			}
		}
		return T{};
	}

protected:
	map<shared_ptr<CTT_PropoertyBase>, std::variant<int, float, double, weak_ptr<void>>> test;
};

