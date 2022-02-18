#include "pch.h"
#include "Visual.h"
DependencyProperty<int> Visual::WidthProperty;
DependencyProperty<shared_ptr<Thinckness>> Visual::ThincknessProperty;
DependencyProperty<string> Visual::TagProperty;

void Visual::TagPropertyChange(DependencyObject obj, DependencyPropertyChangedEventArgs<string> args)
{

}

void Visual::TagPropertyChange1(DependencyObject obj, DependencyPropertyChangedEventArgs<string> args)
{

}
void Visual::WidthPropertyChange(DependencyObject* obj, DependencyPropertyChangedEventArgs<int> args)
{
	Visual* aa = (Visual*)obj;
}


Visual::Visual()
{
	//WidthProperty.Meta.PropertyChangedCallback = [&](auto obj, auto args)
	//{
	//	string str = this->name + " ";
	//	::OutputDebugStringA(str.c_str());
	//};
	
	WidthProperty.Meta.PropertyChangedCallback = std::bind(Visual::WidthPropertyChange, placeholders::_1, placeholders::_2);
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