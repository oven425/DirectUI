#pragma once
#include <functional>
#include <memory>
#include <string>
using namespace std;

namespace DirectUI
{
	class DependencyObject;
}



namespace DirectUI
{
	

	class DependencyProperty
	{
	public:
		static shared_ptr<DependencyProperty> Register(std::function<void(const DependencyObject& sender)> handler);
		//{
		//	shared_ptr<DependencyProperty> property = ::make_shared< DependencyProperty>();
		//	property->DependencyChangeHandler = handler;
		//	return property;
		//}

		wstring m_Name;
		std::function<void(const DependencyObject& sender)> DependencyChangeHandler;
		std::function<void(const DependencyObject& sender)> DependencyChangeHandler1;
	public:
		DependencyProperty() {}
	};

	template<class T>
	struct DependencyPropertyChangeArgs
	{
		T OldValue;
		T NewValue;
	};
	template<class T>
	class DependencyProperty1:public DependencyProperty
	{
	public:
		static shared_ptr<DependencyProperty1> Register(std::function<void(const DependencyObject& sender)> handler)
		{
			shared_ptr<DependencyProperty1> property = ::make_shared< DependencyProperty1>();
			property->DependencyChangeHandler = handler;
			return property;
		}

		wstring m_Name;
		std::function<void(const DependencyObject& sender, const DependencyPropertyChangeArgs<T>& args)> DependencyChangeHandler;
	public:
		DependencyProperty1() {}
	};
}


