#include "pch.h"
#include "CControl.h"
using namespace DirectUI;
using namespace Control;

void CControl::OnSize(float width, float height, float dpiscale)
{
	this->m_DpiScale = dpiscale;
}

void CControl::Measure(float width, float height)
{
	this->DesiredSize.width = width;
	if (this->m_Width > 0)
	{
		if (width < this->m_Width)
		{
			this->DesiredSize.width = width;
		}
		else
		{
			this->DesiredSize.width = this->m_Width;
		}
		this->DesiredSize.width = this->m_Width;
	}
	this->DesiredSize.height = height;
	if (this->m_Height > 0)
	{
		if (height < this->m_Height)
		{
			this->DesiredSize.height = height;
		}
		else
		{
			this->DesiredSize.height = this->m_Height;
		}
		this->DesiredSize.height = this->m_Height;
	}
	//this->DesiredSize.width = this->DesiredSize.width - this->Margin.GetLeft() - this->Margin.GetRight();
	//this->DesiredSize.height = this->DesiredSize.height - this->Margin.GetTop() - this->Margin.GetBottom();
}

void CControl::Arrange(float x, float y, float width, float height)
{
	//float left = x+ this->Margin.GetLeft();
	//float top = y + this->Margin.GetTop();
	//float right = x + width - this->Margin.GetRight();
	//float bottom = y + height - this->Margin.GetBottom();
	float left = x;
	float top = y;
	float right = x + width;
	float bottom = y + height;
	float w = right - left;
	float h = bottom - top;
	if (w != this->DesiredSize.width)
	{
		
		switch (this->GetHorizontalAlignment())
		{
		case HorizontalAlignments::Stretch:
		case HorizontalAlignments::Center:
		{
			left = left + (w - this->DesiredSize.width) / 2;
		}
		break;
		case HorizontalAlignments::Right:
		{
			left = left + (w - this->DesiredSize.width);
		}
		break;
		}
		w = this->DesiredSize.width;
	}
	
	if (h != this->DesiredSize.height)
	{
		switch (this->GetVerticalAlignment())
		{
		case VerticalAlignments::Stretch:
		case VerticalAlignments::Center:
		{
			top = top + (h - this->DesiredSize.height) / 2;
		}
		break;
		case VerticalAlignments::Bottom:
		{
			top = top + (h - this->DesiredSize.height);
		}
		break;
		}
		h = this->DesiredSize.height;
	}
	if (left < 0)
	{
		left = 0;
	}
	if (top < 0)
	{
		top = 0;
	}
	left = left + this->Margin.GetLeft();
	top = top + this->Margin.GetTop();

	this->m_ActualRect.SetX(left);
	this->m_ActualRect.SetY(top);
	this->m_ActualRect.SetWidth(w);
	this->m_ActualRect.SetHeight(h);
}

void CControl::OnRender(ID2D1HwndRenderTarget* pRT)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
	CDirectUI_Rect rc = (this->m_ActualRect) / this->m_DpiScale;
	if (this->Background.use_count() > 0)
	{
		this->Background->Refresh(pRT);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
		pRT->FillRectangle(rc, m_pBlackBrush);
	}
}
