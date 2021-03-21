#pragma once
#include <functional>
#include <memory>
#include <string>
using namespace std;

//#include "CControl.h"
//using namespace DirectUI;
//using namespace Control;
class DependencyObject;
namespace DirectUI
{
	class DependencyProperty
	{
	public:
		static shared_ptr<DependencyProperty> Register(std::function<void(shared_ptr<DependencyProperty> sender)> handler)
		{
			shared_ptr<DependencyProperty> property = ::make_shared< DependencyProperty>();
			property->DependencyChangeHandler = handler;
			return property;
		}
		DependencyProperty(){}
		//DependencyProperty(std::function<void(shared_ptr<int> sender)> changehandler)
		//{
		//	this->DependencyChangeHandler = changehandler;
		//}
		wstring m_Name;
		std::function<void(shared_ptr<DependencyProperty> sender)> DependencyChangeHandler;
	};
}


