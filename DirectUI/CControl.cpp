#include "pch.h"
#include "CControl.h"

using namespace DirectUI;
using namespace Control;

shared_ptr<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>> CControl::BackgroundProperty;

CControl::CControl()
{
	if (!BackgroundProperty)
	{
		BackgroundProperty = ::make_shared<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>>();
		BackgroundProperty->DependencyChangeHandler += std::bind(BackgroundPropertyChange, std::placeholders::_1, std::placeholders::_2);
		BackgroundProperty->m_Name = L"Background";
	}
}

void CControl::CreateRenderBuf(ID2D1RenderTarget* pRT, const CDirectUI_Size& data)
{
	UIElement::CreateRenderBuf(pRT, data, this->Background);
}

void CControl::BackgroundPropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs<shared_ptr<Direct2D::CD2D_Brush>>& args)
{
	CControl& aa = (CControl&)sender;
	aa.Invalidate();
}

void CControl::SetBackground(shared_ptr<Direct2D::CD2D_Brush> data)
{
	this->SetValue(BackgroundProperty, data);
}

shared_ptr<Direct2D::CD2D_Brush> CControl::GetBackground()
{
	return this->GetValue<shared_ptr<Direct2D::CD2D_Brush>>(BackgroundProperty);
}

shared_ptr<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>> CControl::BackgroundPropertyInstance()
{
	return BackgroundProperty;
}

void CControl::OnRender(ID2D1RenderTarget* pRT)
{
	pRT->PushAxisAlignedClip(this->m_ActualRect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	if (this->Background)
	{
		this->Background->Refresh(pRT);
		pRT->FillRectangle(this->m_MeasureRect, *this->Background);
	}

	pRT->PopAxisAlignedClip();
}
