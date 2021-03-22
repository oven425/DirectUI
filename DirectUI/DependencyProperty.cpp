#include "pch.h"
//#include "DependencyProperty.h"
#include "DependencyObject.h"
using namespace DirectUI;

shared_ptr<DependencyProperty> DependencyProperty::Register(std::function<void(const DependencyObject& sender)> handler)
{
	shared_ptr<DependencyProperty> property = ::make_shared<DependencyProperty>();
	property->DependencyChangeHandler = handler;
	return property;
}