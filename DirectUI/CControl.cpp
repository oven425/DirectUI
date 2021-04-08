#include "pch.h"
#include "CControl.h"
using namespace DirectUI;
using namespace Control;

shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>> CControl::BackgroundProperty;

CControl::CControl()
{
	if (!BackgroundProperty)
	{
		BackgroundProperty = ::make_shared<DependencyProperty<Direct2D::CD2D_Brush>>();
		BackgroundProperty->DependencyChangeHandler = std::bind(BackgroundPropertyChange, std::placeholders::_1, std::placeholders::_2);
		BackgroundProperty->m_Name = L"Background";
	}
}

void CControl::CreateRenderBuf(ID2D1RenderTarget* pRT, const CDirectUI_Size& data)
{
	UIElement::CreateRenderBuf(pRT, data, this->Background);
}

void CControl::BackgroundPropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs< Direct2D::CD2D_Brush>& args)
{
	CControl& aa = (CControl&)sender;
	aa.Invalidate();
}

void CControl::SetBackground(shared_ptr<Direct2D::CD2D_Brush> data)
{
	//if (this->m_Background && this->m_Background != data)
	//{
	//	this->m_Background->Release();
	//}
	//this->m_Background = data;
	
	this->SetValue(BackgroundProperty, data);
	//auto obj = this->GetValue<shared_ptr<void>>(BackgroundProperty);
	//shared_ptr<Direct2D::CD2D_Brush> br = static_pointer_cast<Direct2D::CD2D_Brush>(obj);
}

shared_ptr<Direct2D::CD2D_Brush> CControl::GetBackground()
{
	auto obj = this->GetValue<shared_ptr<void>>(BackgroundProperty);
	return  static_pointer_cast<Direct2D::CD2D_Brush>(obj);
}
