#include "pch.h"
#include "CCanvas.h"
using namespace DirectUI;
using namespace Control;


shared_ptr<DependencyProperty<float>> CCanvas::LeftProperty;
shared_ptr<DependencyProperty<float>> CCanvas::TopProperty;
//CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Right;
//CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Bottom;

CCanvas::CCanvas()
{
	if (!LeftProperty)
	{
		LeftProperty = ::make_shared<DependencyProperty<float>>();
		LeftProperty->DependencyChangeHandler += std::bind(LeftPropertyChange, std::placeholders::_1, std::placeholders::_2);
	}
	if (!TopProperty)
	{
		TopProperty = ::make_shared<DependencyProperty<float>>();
		TopProperty->DependencyChangeHandler += std::bind(LeftPropertyChange, std::placeholders::_1, std::placeholders::_2);
	}
	
}

void CCanvas::LeftPropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs<float>& args)
{
	CControl& cc = (CControl&)sender;
	cc.InvalidateArrange();
	cc.Invalidate();
}

void CCanvas::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);
	for (auto oo : this->m_Childs)
	{
		oo->OnRender(this->m_pRenderBuf);
	}

	::CControl::OnRender(pRT);
}

void CCanvas::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	CDirectUI_Size sz = data + this->m_Margin;
	for (auto oo : this->m_Childs)
	{
		CDirectUI_Size child_sz(oo->GetWidth(), oo->GetHieght());
		oo->Measure(child_sz, pRT);
	}
	this->DesiredSize = sz;
}

void CCanvas::Arrange(const CDirectUI_Rect& data)
{
	::CControl::Arrange(data);
	for (auto oo : this->m_Childs)
	{
		float child_x = GetLeft(oo);
		float child_y = GetTop(oo);
		//char msg[256] = { 0 };
		//::sprintf_s(msg, "child_x:%f child_y:%f\r\n", child_x, child_y);
		//::OutputDebugStringA(msg);
		CDirectUI_Rect child_rc(child_x, child_y, child_x+oo->GetWidth(), child_y+oo->GetHieght());
		oo->Arrange(child_rc);
	}
}

void CCanvas::SetLeft(shared_ptr<CControl> element, float data)
{
	element->SetValue(LeftProperty, data);
}

float CCanvas::GetLeft(shared_ptr<UIElement> element)
{
	return element->GetValue<float>(LeftProperty);
}

void CCanvas::SetTop(shared_ptr<CControl> element, float data)
{
	element->SetValue(TopProperty, data);
}

float CCanvas::GetTop(shared_ptr<UIElement> element)
{
	return element->GetValue<float>(TopProperty);
}

//void CCanvas::SetRight(shared_ptr<CControl> element, float data)
//{
//	m_Right.SetValue(element, data);
//}
//
//float CCanvas::GetRight(shared_ptr<CControl> element)
//{
//	return m_Right.GetValue(element);
//}
//
//void CCanvas::SetBottom(shared_ptr<CControl> element, float data)
//{
//	m_Bottom.SetValue(element, data);
//}
//
//float CCanvas::GetBottom(shared_ptr<CControl> element)
//{
//	return m_Bottom.GetValue(element);
//}