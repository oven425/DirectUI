#include "pch.h"
#include "Visual.h"
DependencyProperty<int> Visual::WidthProperty;
DependencyProperty<shared_ptr<Thinckness>> Visual::ThincknessProperty;
DependencyProperty<string> Visual::TagProperty;

Visual::Visual()
{
	//WidthProperty.Meta.PropertyChangedCallback = [&](auto obj, auto args)
	//{
	//	string str = this->name + " ";
	//	::OutputDebugStringA(str.c_str());
	//};

}

Visual::~Visual()
{

}

void Visual::SetTag(DependencyObject& d, string value)
{
	d.SetValue(&Visual::TagProperty, value);
}
string Visual::GetTag(DependencyObject& d)
{
	return d.GetValue(&Visual::TagProperty);
}