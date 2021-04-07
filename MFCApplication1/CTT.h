#pragma once
#include <memory>
#include <variant>
#include <functional>
#include <map>
using namespace std;

#include "CTT_Propoerty.h"

template<class T>
class Event
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
	template<class _Ty1, class _Ty2>
	_NODISCARD shared_ptr<_Ty1> static_pointer_cast11(const shared_ptr<_Ty2>& _Other) noexcept
	{	// static_cast for shared_ptr that properly respects the reference count control block
		const auto _Ptr = static_cast<typename shared_ptr<_Ty1>::element_type *>(_Other.get());
		return (shared_ptr<_Ty1>(_Other, _Ptr));
	}

	template<typename T>
	shared_ptr<T> Trans(shared_ptr<void> src)
	{
		const auto _Ptr = static_cast<typename shared_ptr<T>::element_type *>(src.get());
		return shared_ptr<T>(src, _Ptr);
	}
	map<shared_ptr<CTT_PropoertyBase>, std::variant<int, float, double, weak_ptr<void>>> test;
};

