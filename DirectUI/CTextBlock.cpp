#include "pch.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;

CTextBlock::CTextBlock(const wchar_t* data)
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

	pRT->PushAxisAlignedClip(this->m_ActualRect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	if (this->Background)
	{
		this->Background->Refresh(pRT);
		pRT->FillRectangle(this->m_ActualRect, *this->Background);
	}
	if (this->m_Foreground)
	{
		this->m_Foreground->Refresh(pRT);
		
		pRT->DrawTextLayout(MappingRenderRect1(this->m_ActualRect, this->DesiredSize) , *this->Font, *this->m_Foreground);
	}
	
	pRT->PopAxisAlignedClip();
}

void CTextBlock::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	//CDirectUI_Thinkness margin = this->m_Margin;
	CDirectUI_Size sz1 = data + *this->Margin;
	//width = width - margin.GetLeft() - margin.GetRight();
	//height = height - margin.GetTop() - margin.GetBottom();
	float w = sz1.GetWidth();
	float h = sz1.GetHeight();

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
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = rc.GetWidth();
		}
	}
	if (this->DesiredSize.height < rc.GetHeight())
	{
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = rc.GetHeight();
		}
	}
	::CControl::Arrange(data);
}

void CTextBlock::SetForeground(shared_ptr<Direct2D::CD2D_Brush> data)
{
	if (this->m_Foreground)
	{
		this->m_Foreground->Release();
	}
	this->m_Foreground = data;
}

void CTextBlock::SetText(const wchar_t* data)
{
	this->m_Text = data;
}