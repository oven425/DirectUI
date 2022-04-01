#include "pch.h"
#include "FrameworkElement.h"
shared_ptr<DependencyProperty<double>> FrameworkElement::WidthProperty;
shared_ptr<DependencyProperty<double>> FrameworkElement::HeightProperty;
//https://www.codeproject.com/Articles/5324971/Deep-Dive-into-WPF-Layouting-and-Rendering
//https://docs.microsoft.com/en-us/windows/win32/directcomp/directcomposition-portal
FrameworkElement::FrameworkElement()
{
	if (WidthProperty != nullptr)
	{
		WidthProperty = ::make_shared<DependencyProperty<double>>();
	}

	if (HeightProperty != nullptr)
	{
		HeightProperty = ::make_shared<DependencyProperty<double>>();
	}
}

void FrameworkElement::SetWidth(double data)
{
	this->SetValue(WidthProperty, data);
}

void FrameworkElement::SetHeight(double data)
{
	this->SetValue(HeightProperty, data);
}

double FrameworkElement::GetWidth()
{
	return this->GetValue(WidthProperty);
}

double FrameworkElement::GetHeight()
{
	return this->GetValue(HeightProperty);
}