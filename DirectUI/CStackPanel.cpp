#include "pch.h"
#include "CStackPanel.h"
using namespace DirectUI;
using namespace Control;
#include <numeric>
using namespace std;

shared_ptr<DependencyProperty<int>> CStackPanel::OrientationProperty;

CStackPanel::CStackPanel()
{
	if (!OrientationProperty)
	{
		OrientationProperty = ::make_shared<DependencyProperty<int>>();
	}
	this->Orientation = Orientations::Vertical;
}

void CStackPanel::OnSize(float width, float height, float dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
	for (auto oo : this->m_Childs)
	{
		oo->OnSize(width, height, dpiscale);
	}
}

void CStackPanel::OnRender(ID2D1RenderTarget* pRT)
{
	//this->CreateRenderBuf(pRT, this->DesiredSize);
	//
	//for (auto oo : this->m_Childs)
	//{
	//	oo->OnRender(this->m_pRenderBuf);
	//}

	//::CControl::OnRender(pRT);
	if (this->m_ActualRect == 0)
	{
		return;
	}
	pRT->PushAxisAlignedClip(this->m_ActualRect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	if (this->Background)
	{
		this->Background->Refresh(pRT);
		pRT->FillRectangle(this->m_ActualRect, *this->Background);
	}
	pRT->PopAxisAlignedClip();
	for (auto oo : this->m_Childs)
	{
		oo->OnRender(pRT);
	}
}

void CStackPanel::Measure(const CDirectUI_Rect& data, ID2D1RenderTarget* pRT)
{
	this->m_MeasureRect = 0;
	CDirectUI_Rect stackpanel_rc = data + *this->Margin;
	switch (this->Orientation)
	{
	case Orientations::Vertical:
	{
		CDirectUI_Rect rc = stackpanel_rc;
		float height = 0;
		float width = 0;
		for (auto oo : this->m_Childs)
		{
			rc.SetHeight(0);
			oo->Measure(rc, pRT);
			//this->DesiredSize.height = this->DesiredSize.height + oo->DesiredSize.height;
			rc.SetOffsetY(oo->m_MeasureRect.GetHeight());
			
			height = height + oo->m_MeasureRect.GetHeight();
			//this->m_MeasureRect.SetHeight((*aaa)->m_MeasureRect.GetWidth());
		}
		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<UIElement> c1, shared_ptr<UIElement> c2) {return c1->m_MeasureRect.GetWidth() > c2->m_MeasureRect.GetWidth(); });
		width = (*aaa)->m_MeasureRect.GetWidth();
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			width = stackpanel_rc.GetWidth();
		}
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			height = stackpanel_rc.GetHeight();
		}
		this->m_MeasureRect = ::UIElement::MeasureMapping(stackpanel_rc, CDirectUI_Size(width, height), this->m_HorizontalAlignment, this->m_VerticalAlignment);
	}
	break;
	case Orientations::Horizontal:
	{
		this->DesiredSize.height = stackpanel_rc.GetHeight();
		for (auto oo : this->m_Childs)
		{
			oo->Measure(stackpanel_rc, pRT);
			this->DesiredSize.width = this->DesiredSize.width + oo->DesiredSize.width;
		}

		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<UIElement> c1, shared_ptr<UIElement> c2) {return c1->DesiredSize.height > c2->DesiredSize.height; });
		this->DesiredSize.height = (*aaa)->DesiredSize.height;
	}
	break;
	}
	
}

void CStackPanel::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Size stackpanel_sz = data + *this->Margin;
	switch (this->Orientation)
	{
	case Orientations::Vertical:
	{
		for (auto oo : this->m_Childs)
		{
			oo->Measure(CDirectUI_Size(stackpanel_sz.GetWidth(), 0), pRT);
			this->DesiredSize.height = this->DesiredSize.height + oo->DesiredSize.height;
		}
		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<UIElement> c1, shared_ptr<UIElement> c2) {return c1->DesiredSize.width > c2->DesiredSize.width; });
		this->DesiredSize.width = (*aaa)->DesiredSize.width;
	}
	break;
	case Orientations::Horizontal:
	{
		this->DesiredSize.height = stackpanel_sz.GetHeight();
		for (auto oo : this->m_Childs)
		{
			oo->Measure(CDirectUI_Size(0, stackpanel_sz.GetHeight()), pRT);
			this->DesiredSize.width = this->DesiredSize.width + oo->DesiredSize.width;
		}

		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<UIElement> c1, shared_ptr<UIElement> c2) {return c1->DesiredSize.height > c2->DesiredSize.height; });
		this->DesiredSize.height = (*aaa)->DesiredSize.height;
	}
	break;
	}

	if (this->m_Width > 0 && this->m_Width < this->DesiredSize.width)
	{
		this->DesiredSize.width = this->m_Width;
	}
	else if (this->DesiredSize.width < stackpanel_sz.GetWidth())
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = stackpanel_sz.GetWidth();
		}
	}
	if (this->m_Height > 0 && this->m_Height < this->DesiredSize.height)
	{
		this->DesiredSize.height = this->m_Height;
	}
	else if (this->DesiredSize.height < stackpanel_sz.GetHeight())
	{
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = stackpanel_sz.GetHeight();
		}
	}
}

void CStackPanel::Arrange(const CDirectUI_Rect& data)
{
	CDirectUI_Rect rc = data + *this->Margin;
	float w = this->DesiredSize.width;
	float h = this->DesiredSize.height;
	if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
	{
		if (w > rc.GetWidth() - (*this->Margin).GetLeft() - (*this->Margin).GetRight())
		{
			w = rc.GetWidth();
		}
	}
	if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
	{
		if (h > rc.GetHeight() - (*this->Margin).GetTop() - (*this->Margin).GetBottom())
		{
			h = rc.GetHeight();
		}
	}
	CControl::Arrange(data);
	float y = this->m_ActualRect.GetTop();
	float x = this->m_ActualRect.GetLeft();
	for (auto oo : this->m_Childs)
	{
		oo->GetActualRect() = CDirectUI_Rect(0);
	}
	switch (this->Orientation)
	{
	case Orientations::Vertical:
	{
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(CDirectUI_Rect(x, y, this->m_ActualRect.GetRight(), y));
			//oo->GetActualRect() = ::UIElement::MappingRenderRect1(oo->GetActualRect(), oo->DesiredSize, this->m_HorizontalAlignment, this->m_VerticalAlignment);
			y = y + oo->GetActualRect().GetHeight();
			float b1 = oo->GetActualRect().GetBottom();
			float b2 = this->m_ActualRect.GetBottom();
			if (b1 > b2)
			{
				oo->GetActualRect().SetBottom(this->m_ActualRect.GetBottom());
				break;
			}
		}
	}
	break;
	case Orientations::Horizontal:
	{
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(CDirectUI_Rect(x, y, x+oo->DesiredSize.width, h));
			x = x + oo->GetActualRect().GetWidth();
		}
	}
	break;
	}

	
}

void CStackPanel::SetOrientation(Orientations data)
{
	this->SetValue(OrientationProperty, (int)data);
}

Orientations CStackPanel::GetOrientation() 
{ 
	return (Orientations)this->GetValue<int>(OrientationProperty);
}