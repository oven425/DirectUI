#pragma once
#include <map>
#include <variant>
#include <type_traits>
using namespace std;

#include "DispatchObject.h"
#include "DependencyProperty.h"
class DependencyObject : public DispatchObject
{
public:
	template<class T>
	void SetValue(shared_ptr<DependencyProperty<T>> dp, T data)
	{
		if (this->m_Saves.find(dp) != this->m_Saves.end())
		{
			if (dp->Meta.PropertyChangedCallback)
			{
				DependencyPropertyChangedEventArgs<T> args;
				args.NewValue = data;
				args.OldValue = this->GetValue(dp);
				if (args.NewValue != args.OldValue)
				{
					dp->Meta.PropertyChangedCallback(this, args);
				}
			}

			this->m_Saves[dp] = data;
		}
		else
		{
			this->m_Saves[dp] = data;
		}
		
	}

	template<class T>
	constexpr T GetValue(shared_ptr<DependencyProperty<T>> dp)
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			if (this->m_Saves.find(dp) != this->m_Saves.end())
			{
				auto var = this->m_Saves[dp];
				auto value = std::get<T>(var);
				return value;
			}
			return T{};
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			if (this->m_Saves.find(dp) != this->m_Saves.end())
			{
				auto var = this->m_Saves[dp];
				auto value = std::get<T>(var);
				return value;
			}
			return T{};
		}
		else
		{
			if (this->m_Saves.find(dp) != this->m_Saves.end())
			{
				auto var = this->m_Saves[dp];
				auto aa = std::get<shared_ptr<void>>(var);
				const auto _Ptr = static_cast<typename T::element_type *>(aa.get());
				return (T(aa, _Ptr));
			}
			//else
			//{
			//	return (*dp).m_Default;
			//}

		}
		
		return T{};
	}
private:
	map<shared_ptr<void>, std::variant<int, unsigned int, double, string, shared_ptr<void>>> m_Saves;
	//map<const void*, shared_ptr<void>> m_PropertyMetadatas;
};

