#include "pch.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;



void CTextBlock::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}

	
	this->CreateRenderBuf(pRT, this->DesiredSize);
	HRESULT hr = S_OK;
	


	if (this->m_Foreground)
	{
		this->m_Foreground->Refresh(this->m_pRenderBuf);
		CDirectUI_Rect rc = this->DesiredSize;
		this->m_pRenderBuf->DrawTextLayout(rc, *this->Font, *this->m_Foreground);
		//rc = CDirectUI_Rect(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		//pCompatibleRenderTarget->DrawTextW(this->m_Text.c_str(), this->m_Text.length(), *this->Font, rc / this->m_DpiScale, *this->Foreground);
	}


	::CControl::OnRender(pRT, calculate_dpi);
}

void CTextBlock::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	//CDirectUI_Thinkness margin = this->m_Margin;
	CDirectUI_Size sz1 = data + this->m_Margin;
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
	//else if (sz.width < sz1.GetWidth())
	//{
	//	if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
	//	{
	//		this->DesiredSize.width = sz1.GetWidth();
	//	}
	//}
	this->DesiredSize.height = sz.height;
	if (this->m_Height > 0 && this->m_Height < sz.height)
	{
		this->DesiredSize.height = this->m_Height;
	}
	//else if (sz.height < sz1.GetHeight())
	//{
	//	if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
	//	{
	//		this->DesiredSize.height = sz1.GetHeight();
	//	}
	//}
}

//void CTextBlock::Measure(float width, float height, ID2D1RenderTarget* pRT)
//{
//	this->DesiredSize.width = this->DesiredSize.height = 0;
//	CDirectUI_Thinkness margin = this->m_Margin;
//	width = width - margin.GetLeft() - margin.GetRight();
//	height = height - margin.GetTop() - margin.GetBottom();
//	float w = width;
//	float h = height;
//
//	if (this->m_Width > 0)
//	{
//		w = this->m_Width;
//	}
//	if (this->m_Height > 0)
//	{
//		h = this->m_Height;
//	}
//	D2D1_SIZE_F sz = this->Font->GetTextSize(this->m_Text.c_str(), w, h);
//	this->DesiredSize.width = sz.width;
//	if (this->m_Width > 0 && this->m_Width<sz.width)
//	{
//		this->DesiredSize.width = this->m_Width;
//	}
//	else if (sz.width < width)
//	{
//		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
//		{
//			this->DesiredSize.width = width;
//		}
//	}
//	this->DesiredSize.height = sz.height;
//	if (this->m_Height > 0 && this->m_Height < sz.height)
//	{
//		this->DesiredSize.height = this->m_Height;
//	}
//	else if(sz.height < height)
//	{
//		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
//		{
//			this->DesiredSize.height = height;
//		}
//	}
//}

void CTextBlock::Arrange(float x, float y, float width, float height)
{
	if (this->DesiredSize.width < width)
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = width;
		}
	}
	if(this->DesiredSize.height < height)
	{
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = height;
		}
	}
	::CControl::Arrange(x, y, width, height);
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