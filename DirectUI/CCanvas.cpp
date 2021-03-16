#include "pch.h"
#include "CCanvas.h"
using namespace DirectUI;
using namespace Control;

CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Left;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Top;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Right;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Bottom;


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
		CDirectUI_Rect child_rc(child_x, child_y, child_x+oo->GetWidth(), child_y+oo->GetHieght());
		oo->Arrange(child_rc);
	}
}

void CCanvas::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
}

void CCanvas::SetLeft(shared_ptr<CControl> element, float data)
{
	m_Left.SetValue(element, data);
}

float CCanvas::GetLeft(shared_ptr<CControl> element)
{
	return m_Left.GetValue(element);
}

void CCanvas::SetTop(shared_ptr<CControl> element, float data)
{
	m_Top.SetValue(element, data);
}

float CCanvas::GetTop(shared_ptr<CControl> element)
{
	return m_Top.GetValue(element);
}

void CCanvas::SetRight(shared_ptr<CControl> element, float data)
{
	m_Right.SetValue(element, data);
}

float CCanvas::GetRight(shared_ptr<CControl> element)
{
	return m_Right.GetValue(element);
}

void CCanvas::SetBottom(shared_ptr<CControl> element, float data)
{
	m_Bottom.SetValue(element, data);
}

float CCanvas::GetBottom(shared_ptr<CControl> element)
{
	return m_Bottom.GetValue(element);
}