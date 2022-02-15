#include "pch.h"
#include "Visual.h"
DependencyProperty<int> Visual::WidthProperty;
DependencyProperty<shared_ptr<Thinckness>> Visual::ThincknessProperty;
DependencyProperty<string> Visual::TagProperty;

Visual::Visual()
{
	auto meta_width = ::make_shared<PropertyMetadata<int>>();
	(*meta_width).PropertyChangedCallback = [](auto obj, auto args)
	{

	};
	this->SetPropertyMetadata(&Visual::WidthProperty, meta_width);
	this->GetPropertyMetadata(&Visual::WidthProperty);
	auto meta_thinckness = ::make_shared<PropertyMetadata<shared_ptr<Thinckness>>>();

	(*meta_thinckness).PropertyChangedCallback = [](auto obj, auto args)
	{

	};

	shared_ptr<void> sss = meta_thinckness;
	shared_ptr<PropertyMetadata<shared_ptr<Thinckness>>> sss1 = static_pointer_cast<PropertyMetadata<shared_ptr<Thinckness>>>(sss);
	auto pppp = meta_thinckness.get();


	this->SetPropertyMetadata(&Visual::ThincknessProperty, meta_thinckness);
	this->GetPropertyMetadata(&Visual::ThincknessProperty);
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