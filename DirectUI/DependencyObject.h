#pragma once
#include <map>
#include <variant>
using namespace std;

#include "DependencyProperty.h"

namespace DirectUI
{
	class DependencyObject:public enable_shared_from_this<DependencyObject>
	{
	//protected:
	//	template<typename T>
	//	void Change(shared_ptr<DependencyProperty<T>> dp, T old_val, T new_val)
	//	{
	//		if (dp && new_val != old_val)
	//		{
	//			auto args = DependencyPropertyChangeArgs<T>();
	//			args.OldValue = old_val;
	//			args.NewValue = new_val;
	//			if (dp->DependencyChangeHandler)
	//			{
	//				dp->DependencyChangeHandler(*this, args);
	//			}
	//		}
	//	}
	public:
		template<typename T>
		void SetValue(shared_ptr<DependencyProperty<T>> dp, shared_ptr<T> data)
		{
			if (!dp)
			{
				return;
			}
			shared_ptr<void> old;
			bool hasold = false;
			auto find = this->m_Save.find(dp);
			if (find != this->m_Save.end())
			{
				try
				{
					old = std::get<shared_ptr<void>>(find->second);
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
				auto args = DependencyPropertyChangeArgs<T>();
				args.OldValue = *static_pointer_cast<T>(old);
				args.NewValue = *data;
				if (dp->DependencyChangeHandler)
				{
					dp->DependencyChangeHandler(*this, args);
				}
			}
			m_Save[dp] = data;
		}

		template<typename T>
		void SetValue(shared_ptr<DependencyProperty<T>> dp, T data)
		{
			if (!dp)
			{
				return;
			}
			T old;
			bool hasold = false;
			auto find = this->m_Save.find(dp);
			if (find != this->m_Save.end())
			{
				try
				{
					old = std::get<T>(find->second);
					hasold = true;
				}
				catch (const std::bad_variant_access&)
				{
				}
			}
			if (hasold == true && data != old)
			{
				auto args = DependencyPropertyChangeArgs<T>();
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
			if (dp)
			{
				auto find = this->m_Save.find(dp);
				if (find != this->m_Save.end())
				{
					try
					{
						return std::get<T>(find->second);
					}
					catch (const std::bad_variant_access& err)
					{
						//::OutputDebugStringA("");
					}
				}
			}

			return T{};
		}

		template<typename T>
		void ClearValue(shared_ptr<DependencyProperty<T>> dp)
		{
			if (dp)
			{
				auto find = this->m_Save.find(dp);
				if (find != this->m_Save.end())
				{
					try
					{
						this->m_Save.erase(find);
					}
					catch (const std::bad_variant_access& err)
					{
						//::OutputDebugStringA("");
					}
				}
			}
		}


	protected:
		map<shared_ptr<DependencyPropertyBase>, std::variant<bool, char, unsigned char, short, unsigned short, int, unsigned int, __int64, unsigned __int64, float, double, string, wstring, shared_ptr<void>>> m_Save;
	};
}


