#include "pch.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;
shared_ptr<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>> CTextBlock::ForegroundProperty;

CTextBlock::CTextBlock() 
{
	if (!ForegroundProperty)
	{
		ForegroundProperty = ::make_shared<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>>();
		ForegroundProperty->m_Name = L"Foreground";
	}
}

CTextBlock::CTextBlock(const wchar_t* data)
	: CTextBlock()
{
	this->m_Text = data;
}

void CTextBlock::OnRender(ID2D1RenderTarget* pRT)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
	
	//this->CreateRenderBuf(pRT, this->DesiredSize);
	//HRESULT hr = S_OK;
	//if (this->m_Foreground)
	//{
	//	this->m_Foreground->Refresh(this->m_pRenderBuf);
	//	CDirectUI_Rect rc = this->DesiredSize;
	//	this->m_pRenderBuf->DrawTextLayout(rc, *this->Font, *this->m_Foreground);
	//}

	//::CControl::OnRender(pRT);

	//pRT->PushAxisAlignedClip(this->m_ActualRect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//if (this->Background)
	//{
	//	this->Background->Refresh(pRT);
	//	pRT->FillRectangle(this->m_ActualRect, *this->Background);
	//}
	//if (this->Foreground)
	//{
	//	this->Foreground->Refresh(pRT);
	//	
	//	pRT->DrawTextLayout(MappingRenderRect1(this->m_ActualRect, this->DesiredSize, this->m_HorizontalAlignment, this->m_VerticalAlignment) , *this->Font, *this->Foreground);
	//}
	//
	//pRT->PopAxisAlignedClip();

	//pRT->PushAxisAlignedClip(this->m_ActualRect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	if (this->Background)
	{
		this->Background->Refresh(pRT);
		//pRT->FillRectangle(this->m_MeasureRect, *this->Background);
		pRT->DrawRectangle(this->m_ActualRect, *this->Background);
	}
	if (this->Foreground)
	{
		this->Foreground->Refresh(pRT);

		pRT->DrawTextLayout(this->m_MeasureRect, *this->Font, *this->Foreground);
	}

	//pRT->PopAxisAlignedClip();
}

void CTextBlock::Measure(const CDirectUI_Rect& data, ID2D1RenderTarget* pRT)
{
	this->m_MeasureRect = 0;
	
	D2D1_SIZE_F sz = this->Font->GetTextSize(this->m_Text.c_str(), 0, 0);

	CDirectUI_Rect margin_rc = data + *this->Margin;
	CDirectUI_Rect rc = data;
	if (data.GetHeight() == 0)
	{
		rc.SetHeight(margin_rc.GetHeight());
	}
	else if (this->VerticalAlignment == VerticalAlignments::Stretch)
	{
		sz.height = margin_rc.GetHeight();
		rc.SetHeight(margin_rc.GetHeight());
	}
	if (data.GetWidth() == 0)
	{
		rc.SetWidth(margin_rc.GetWidth());
	}
	else if (this->HorizontalAlignment == HorizontalAlignments::Stretch)
	{
		sz.width = margin_rc.GetWidth();
		rc.SetWidth(margin_rc.GetWidth());
	}
	
	this->m_MeasureRect = ::UIElement::MeasureMapping(rc, sz, this->HorizontalAlignment, this->VerticalAlignment);
	//switch (this->m_HorizontalAlignment)
	//{
	//case HorizontalAlignments::Stretch:
	//{
	//	this->m_MeasureRect.SetLeft(rc.GetLeft());
	//	this->m_MeasureRect.SetWidth(rc.GetWidth());
	//}
	//break;
	//case HorizontalAlignments::Left:
	//{
	//	float left = rc.GetLeft();
	//	this->m_MeasureRect.SetLeft(left);
	//	this->m_MeasureRect.SetWidth(sz.width);
	//}
	//break;
	//case HorizontalAlignments::Center:
	//{
	//	float left = rc.GetLeft();
	//	left = left + (rc.GetWidth() - sz.width)/2;
	//	this->m_MeasureRect.SetLeft(left);
	//	this->m_MeasureRect.SetWidth(sz.width);
	//}
	//break;
	//case HorizontalAlignments::Right:
	//{
	//	float left = rc.GetLeft();
	//	left = left + rc.GetWidth() - sz.width;
	//	this->m_MeasureRect.SetLeft(left);
	//	this->m_MeasureRect.SetWidth(sz.width);
	//}
	//break;
	//}

	//switch (this->m_VerticalAlignment)
	//{
	//case VerticalAlignments::Stretch:
	//{
	//	this->m_MeasureRect.SetTop(rc.GetTop());
	//	this->m_MeasureRect.SetHeight(rc.GetHeight());
	//}
	//break;
	//case VerticalAlignments::Top:
	//{
	//	float top = rc.GetTop();
	//	this->m_MeasureRect.SetTop(top);
	//	this->m_MeasureRect.SetHeight(sz.height);
	//}
	//break;
	//case VerticalAlignments::Center:
	//{
	//	float top = rc.GetTop();
	//	top = top + (rc.GetHeight() - sz.height)/2;
	//	this->m_MeasureRect.SetTop(top);
	//	this->m_MeasureRect.SetHeight(sz.height);
	//}
	//break;
	//case VerticalAlignments::Bottom:
	//{
	//	float top = rc.GetTop();
	//	top = top + rc.GetHeight() - sz.height;
	//	this->m_MeasureRect.SetTop(top);
	//	this->m_MeasureRect.SetHeight(sz.height);
	//}
	//break;
	//}
}

void CTextBlock::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Size sz1 = data + *this->Margin;

	float w = sz1.GetWidth();
	float h = sz1.GetHeight();
	if (data.GetHeight() == 0)
	{
		h = 0;
	}
	if (this->m_Width > 0)
	{
		w = this->m_Width;
	}
	if (this->m_Height > 0)
	{
		h = this->m_Height;
	}
	D2D1_SIZE_F sz = this->Font->GetTextSize(this->m_Text.c_str(), w, h);
	this->DesiredSize.width = sz.width;
	if (this->m_Width > 0 && this->m_Width < sz.width)
	{
		this->DesiredSize.width = this->m_Width;
	}

	this->DesiredSize.height = sz.height;
	if (data.GetHeight() == 0)
	{
		this->DesiredSize.height = this->DesiredSize.height + this->Margin->GetTop() + this->Margin->GetBottom();
	}
	if (this->m_Height > 0 && this->m_Height < sz.height)
	{
		this->DesiredSize.height = this->m_Height;
	}

}

void CTextBlock::Arrange(const CDirectUI_Rect& data)
{
	CDirectUI_Rect rc = data + *this->Margin;
	if (this->DesiredSize.width < rc.GetWidth())
	{
		if (this->HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = rc.GetWidth();
		}
	}
	if (this->DesiredSize.height < rc.GetHeight())
	{
		if (this->VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = rc.GetHeight();
		}
	}
	::CControl::Arrange(data);
}

void CTextBlock::SetForeground(shared_ptr<Direct2D::CD2D_Brush> data)
{
	//if (this->m_Foreground)
	//{
	//	this->m_Foreground->Release();
	//}
	//this->m_Foreground = data;
	this->SetValue(ForegroundProperty, data);
}

shared_ptr<Direct2D::CD2D_Brush> CTextBlock::GetForeground()
{
	return this->GetValue<shared_ptr<Direct2D::CD2D_Brush>>(ForegroundProperty);
}

void CTextBlock::SetText(const wchar_t* data)
{
	this->m_Text = data;
}