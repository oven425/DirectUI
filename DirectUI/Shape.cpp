#include "pch.h"
#include "Shape.h"
using namespace DirectUI;
using namespace Shapes;

shared_ptr<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>> Shape::StrokeProperty;
shared_ptr<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>> Shape::FillProperty;
shared_ptr<DependencyProperty<float>> Shape::StrokeThicknessProperty;
shared_ptr<DependencyProperty<int>> Shape::StretchProperty;

Shape::Shape()
{
	if (!StrokeProperty)
	{
		StrokeProperty = ::make_shared <DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>>();
		StrokeProperty->m_Name = L"Stroke";
		//StrokeProperty->DependencyChangeHandler = std::bind(StrokePropertyChange, std::placeholders::_1, std::placeholders::_2);
	}
	if (!FillProperty)
	{
		FillProperty = ::make_shared<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>>();
		StrokeProperty->m_Name = L"Fill";
	}
	if (!StretchProperty)
	{
		StretchProperty = ::make_shared<DependencyProperty<int>>();
		StrokeProperty->m_Name = L"Stretch";
	}
	this->SetValue(StretchProperty, int(Control::Stretchs::Fill));
	if (!StrokeThicknessProperty)
	{
		StrokeThicknessProperty = ::make_shared <DependencyProperty<float>>();
		StrokeThicknessProperty->m_Name = L"StrokeThickness";
	}
}

void Shape::SetStretch(Control::Stretchs data)
{ 
	this->SetValue(StretchProperty, (int)data); 
}

Control::Stretchs Shape::GetStretch() 
{ 
	return (Control::Stretchs)this->GetValue<int>(StretchProperty); 
}

void Shape::SetFill(shared_ptr<DirectUI::Direct2D::CD2D_Brush> data)
{
	this->SetValue(FillProperty, data);
}

shared_ptr<Direct2D::CD2D_Brush> Shape::GetFill()
{
	//auto obj = this->GetValue<shared_ptr<void>>(FillProperty);
	//return  static_pointer_cast<Direct2D::CD2D_Brush>(obj);
	return  this->GetValue<shared_ptr<Direct2D::CD2D_Brush>>(FillProperty);
	return nullptr;
}

void Shape::SetStroke(shared_ptr<Direct2D::CD2D_Brush> data)
{
	this->SetValue(StrokeProperty, data);
}

shared_ptr<Direct2D::CD2D_Brush> Shape::GetStroke()
{
	//auto obj = this->GetValue<shared_ptr<void>>(StrokeProperty);
	return  this->GetValue<shared_ptr<Direct2D::CD2D_Brush>>(StrokeProperty);
	return nullptr;
}

void Shape::SetStrokeThickness(float data)
{
	this->SetValue(StrokeThicknessProperty, data);
}

float Shape::GetStrokeThickness()
{
	return this->GetValue<float>(StrokeThicknessProperty);
}
