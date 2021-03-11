#include "pch.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;

#define Test

void CTextBlock::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
#ifdef Test
	
	this->CreateRenderBuf(pRT, this->DesiredSize);
	HRESULT hr = S_OK;
	

	//this->m_pRenderBuf->BeginDraw();

	//if (this->m_Background)
	//{
	//	this->m_Background->Refresh(this->m_pRenderBuf);
	//	CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
	//	//CDirectUI_Rect rc(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	//	this->m_pRenderBuf->FillRectangle(rc, *this->m_Background);
	//}
	if (this->m_Foreground)
	{
		this->m_Foreground->Refresh(this->m_pRenderBuf);
		CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
		this->m_pRenderBuf->DrawTextLayout(rc, *this->Font, *this->m_Foreground);
		//rc = CDirectUI_Rect(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		//pCompatibleRenderTarget->DrawTextW(this->m_Text.c_str(), this->m_Text.length(), *this->Font, rc / this->m_DpiScale, *this->Foreground);
	}


	//this->m_pRenderBuf->EndDraw();
	::CControl::OnRender(pRT, calculate_dpi);
	//ID2D1Bitmap* bmp = NULL;
	//this->m_pRenderBuf->GetBitmap(&bmp);
	//CDirectUI_Rect rc_dst = this->m_ActualRect / this->m_DpiScale;
	//CDirectUI_Rect rc_src(0, 0, this->DesiredSize.width, this->DesiredSize.height);
	////CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	//rc_src = this->MappingRenderRect(this->m_ActualRect, this->DesiredSize);
	////if (this->m_ActualRect.GetWidth() < this->DesiredSize.width)
	////{
	////	rc_src.SetX(this->DesiredSize.width - this->m_ActualRect.GetWidth());
	////}
	////CTrace::WriteLine(L"%s render: %s  Desire w:%f h:%f", this->Name.c_str(), rc_src.ToString().c_str(), rc_src.GetWidth(), rc_src.GetHeight());
	////float w1 = rc_dst.GetWidth();
	////float w2 = rc_src.GetWidth();
	//pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);


	//bmp->Release();
	//this->m_pRenderBuf->Release();
	//this->m_pRenderBuf = NULL;
#else
	if (this->Background)
	{
		this->Background->Refresh(pRT);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
		CDirectUI_Rect rc(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		pRT->FillRectangle(this->m_ActualRect / this->m_DpiScale, m_pBlackBrush);
	}
	if (this->Foreground)
	{
		this->Foreground->Refresh(pRT);
		CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
		pRT->DrawTextW(this->m_Text.c_str(), this->m_Text.length(), *this->Font, this->m_ActualRect / this->m_DpiScale, *this->Foreground);
	}
#endif

}

void CTextBlock::Measure(CDirectUI_Size& data, ID2D1RenderTarget* pRT)
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
	else if (sz.width < sz1.GetWidth())
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = sz1.GetWidth();
		}
	}
	this->DesiredSize.height = sz.height;
	if (this->m_Height > 0 && this->m_Height < sz.height)
	{
		this->DesiredSize.height = this->m_Height;
	}
	else if (sz.height < sz1.GetHeight())
	{
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = sz1.GetHeight();
		}
	}
}

void CTextBlock::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Thinkness margin = this->m_Margin;
	width = width - margin.GetLeft() - margin.GetRight();
	height = height - margin.GetTop() - margin.GetBottom();
	float w = width;
	float h = height;

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
	if (this->m_Width > 0 && this->m_Width<sz.width)
	{
		this->DesiredSize.width = this->m_Width;
	}
	else if (sz.width < width)
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = width;
		}
	}
	this->DesiredSize.height = sz.height;
	if (this->m_Height > 0 && this->m_Height < sz.height)
	{
		this->DesiredSize.height = this->m_Height;
	}
	else if(sz.height < height)
	{
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = height;
		}
	}
}

void CTextBlock::Arrange(float x, float y, float width, float height)
{
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