#include "pch.h"
#include "DependencyObject.h"
using namespace DirectUI;
void DependencyObject::SetValue(shared_ptr<DependencyProperty> dp, float value)
{
	this->m_Save_float[dp] = value;
	dp->DependencyChangeHandler();
}