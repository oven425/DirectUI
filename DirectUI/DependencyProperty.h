#pragma once
#include <functional>
#include <string>
using namespace std;

namespace DirectUI
{
	class DependencyProperty
	{
	public:
		DependencyProperty(){}
		DependencyProperty(std::function<void()> changehandler)
		{
			this->DependencyChangeHandler = changehandler;
		}
		wstring m_Name;
		std::function<void()> DependencyChangeHandler;
	};
}


