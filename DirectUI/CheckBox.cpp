#include "pch.h"
#include "CheckBox.h"
using namespace DirectUI;
using namespace Control;

shared_ptr<DependencyProperty<bool>> CheckBox::IsCheckedProperty;

CheckBox::CheckBox()
{
	if (!IsCheckedProperty)
	{
		IsCheckedProperty = ::make_shared<DependencyProperty<bool>>();
	}
}