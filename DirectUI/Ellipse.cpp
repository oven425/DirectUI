#include "pch.h"
#include "Ellipse.h"
using namespace DirectUI;
using namespace Shapes;

shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>> Ellipse::StrokeProperty;
shared_ptr<DependencyProperty<float>> Ellipse::StrokeThicknessProperty;

Ellipse::Ellipse()
{
	if (!StrokeProperty)
	{
		StrokeProperty = ::make_shared <DependencyProperty<Direct2D::CD2D_Brush>>();
		StrokeProperty->m_Name = L"Stroke";
		//StrokeProperty->DependencyChangeHandler = std::bind(StrokePropertyChange, std::placeholders::_1, std::placeholders::_2);
	}

	if (!StrokeThicknessProperty)
	{
		StrokeThicknessProperty = ::make_shared <DependencyProperty<float>>();
		StrokeThicknessProperty->m_Name = L"StrokeThickness";
	}
}

void Ellipse::StrokePropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs<Direct2D::CD2D_Brush>& args)
{

}

void Ellipse::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	::Control::UIElement::Measure(data, pRT);
}

void Ellipse::Arrange(const CDirectUI_Rect& data)
{
	::Control::UIElement::Arrange(data);
}

void Ellipse::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize, false);
	if (this->Background)
	{
		this->m_pRenderBuf->FillEllipse(this->m_ActualRect, *this->Background);
	}
	if (this->StrokeThickness>0 && this->Stroke)
	{
		this->Stroke->Refresh(pRT);
		auto br = *this->Stroke;
		this->m_pRenderBuf->DrawEllipse(this->m_ActualRect+this->StrokeThickness/2, *this->Stroke, this->StrokeThickness);
	}

	Control::UIElement::OnRender(pRT);
	
}

void Ellipse::SetStroke(shared_ptr<Direct2D::CD2D_Brush> data)
{
	this->SetValue(StrokeProperty, data);
}

shared_ptr<Direct2D::CD2D_Brush> Ellipse::GetStroke()
{
	auto obj = this->GetValue<shared_ptr<void>>(StrokeProperty);
	return  static_pointer_cast<Direct2D::CD2D_Brush>(obj);
}

void Ellipse::SetStrokeThickness(float data)
{
	this->SetValue(StrokeThicknessProperty, data);
}

float Ellipse::GetStrokeThickness()
{
	return this->GetValue<float>(StrokeThicknessProperty);
}