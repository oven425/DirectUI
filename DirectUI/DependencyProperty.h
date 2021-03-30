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
	class DependencyPropertyBase
	{
	public:
		static shared_ptr<DependencyPropertyBase> Register(std::function<void(const DependencyObject& sender)> handler);
		//{
		//	shared_ptr<DependencyProperty> property = ::make_shared< DependencyProperty>();
		//	property->DependencyChangeHandler = handler;
		//	return property;
		//}

		wstring m_Name;
		//std::function<void(const DependencyObject& sender)> DependencyChangeHandler;
	public:
		DependencyPropertyBase() {}
	};

	template<class T>
	struct DependencyPropertyChangeArgs
	{
		T OldValue;
		T NewValue;
	};
	
	template<class T>
	class DependencyProperty : public DependencyPropertyBase
	{
	public:
		//static shared_ptr<DependencyProperty> Register(std::function<void(const DependencyObject& sender)> handler)
		//{
		//	shared_ptr<DependencyProperty> property = ::make_shared< DependencyProperty>();
		//	property->DependencyChangeHandler = handler;
		//	return property;
		//}

		std::function<void(const DependencyObject& sender, const DependencyPropertyChangeArgs<T>& args)> DependencyChangeHandler;
	public:
		DependencyProperty() {}
		DependencyProperty<T> Create()
		{
			return DependencyProperty<T>();
		}
	};
}


