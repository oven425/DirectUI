#pragma once
#include <map>
#include <any>
using namespace std;

#include "DependencyProperty.h"

namespace DirectUI
{
	class DependencyObject
	{
	public:
		void SetValue(shared_ptr<DependencyProperty> dp, float value);

		template <typename T>
		T GetValue(DependencyProperty dp, T value)
		{

		}
	protected:
		map<shared_ptr<DependencyProperty>, float> m_Save_float;
		map<DependencyProperty, int> m_Save;
	};
}


