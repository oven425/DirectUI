#pragma once
#include <map>
#include <variant>
#include <type_traits>
using namespace std;

#include "DispatchObject.h"
#include "DependencyProperty.h"
class DependencyObject:public DispatchObject
{
public:
	template<class T>
	void SetValue(const DependencyProperty<T>* dp, T data)
	{
		this->m_Saves[dp] = data;
	}

	//template<class T>
	//T GetValue(const DependencyProperty<T>* dp)
	//{
	//	if (this->m_Saves.find(dp) != this->m_Saves.end())
	//	{
	//		auto var = this->m_Saves[dp];
	//		auto value = std::get<T>(var);
	//		return value;
	//	}
	//	return T{};
	//}

	template <typename T>
	auto get_value(T t) {
		if constexpr (std::is_pointer_v<T>)
			return *t; // deduces return type to int for T = int*
		else if constexpr (std::is_arithmetic<T>)
			return t;
		else
			return t;  // deduces return type to int for T = int
	}

	template<class T>
	constexpr auto GetValue(const DependencyProperty<T>* dp)
	{
		if constexpr (std::is_arithmetic<T>)
		{
		//	//if (this->m_Saves.find(dp) != this->m_Saves.end())
		//	//{
		//	//	auto var = this->m_Saves[dp];
		//	//	auto value = std::get<T>(var);
		//	//	return value;
		//	//}
		//	//return T{};
		}
		//else
		//{
		//	if (this->m_Saves.find(dp) != this->m_Saves.end())
		//	{
		//		auto var = this->m_Saves[dp];
		//		auto aa = std::get<shared_ptr<void>>(var->second);
		//		const auto _Ptr = static_cast<typename T::element_type *>(aa.get());
		//		return (T(aa, _Ptr));
		//	}
		//	else
		//	{
		//		return (*dp).m_Default;
		//	}

		//}
		
		return T{};
	}
private:
	map<const void*, std::variant<int, unsigned int, shared_ptr<void>>> m_Saves;
};

