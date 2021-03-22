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

	public:
		DependencyProperty() {}
	};
}


