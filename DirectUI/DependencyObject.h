#pragma once
#include <map>
#include <variant>
using namespace std;

#include "DependencyProperty.h"

namespace DirectUI
{
	class DependencyObject:public enable_shared_from_this<DependencyObject>
	{
	public:
		template<typename T>
		void SetValue(shared_ptr<DependencyProperty<T>> dp, shared_ptr<T> data)
		{
			shared_ptr<void> old;
			bool hasold = false;
			auto find = this->m_Save.find(dp);
			if (find != this->m_Save.end())
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
				if (dp->DependencyChangeHandler)
				{
					dp->DependencyChangeHandler(*this, args);
				}
			}
			m_Save[dp] = data;
		}

		template<typename T>
		void SetValue(shared_ptr<DependencyProperty<T>> dp, int data)
		{
			int old;
			bool hasold = false;
			auto find = this->m_Save.find(dp);
			if (find != this->m_Save.end())
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
				if (dp->DependencyChangeHandler)
				{
					dp->DependencyChangeHandler(*this, args);
				}
			}
			m_Save[dp] = data;
		}
		
		template<typename T, typename T1>
		T GetValue(shared_ptr<DependencyProperty<T1>> dp)
		{
			auto find = this->m_Save.find(dp);
			if (find != this->m_Save.end())
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
		map<shared_ptr<DependencyPropertyBase>, std::variant<char, unsigned char, short, unsigned short, int, unsigned int, __int64, unsigned __int64, float, double, string, wstring, weak_ptr<void>>> m_Save;
	};
}


