#include "pch.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;

void CTextBlock::OnRender(ID2D1RenderTarget* pRT)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
	//ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	//HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);



	//pCompatibleRenderTarget->BeginDraw();

	if (this->Background)
	{
		//this->Background->Release();
		this->Background->Refresh(pRT);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
		CDirectUI_Rect rc(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		pRT->FillRectangle(rc, m_pBlackBrush);


	}
	if (this->Foreground)
	{
		this->Foreground->Refresh(pRT);
		CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
		pRT->DrawTextW(this->m_Text.c_str(), this->m_Text.length(), *this->Font, rc, *this->Foreground);
	}



	//pCompatibleRenderTarget->EndDraw();
	//ID2D1Bitmap* bmp = NULL;
	//pCompatibleRenderTarget->GetBitmap(&bmp);
	//CDirectUI_Rect rc_dst = this->m_ActualRect / this->m_DpiScale;
	//CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	//pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);


	//bmp->Release();
	//pCompatibleRenderTarget->Release();


	
	
}

void CTextBlock::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	D2D1_SIZE_F sz = this->Font->GetTextSize(this->m_Text.c_str());
	this->DesiredSize.width = sz.width;
	this->DesiredSize.height = sz.height;
}

void CTextBlock::Arrange(float x, float y, float width, float height)
{
	float left = x;
	float top = y;
	float right = left + width;
	float bottom = top + height;
	float w = right - left;
	float h = bottom - top;
	switch (this->m_HorizontalAlignment)
	{
	case HorizontalAlignments::Stretch:
	{
		
	}
	break;
	case HorizontalAlignments::Center:
	{
		w = this->DesiredSize.width;
		left = left+(width - w) / 2;
	}
	break;
	}
	switch (this->m_VerticalAlignment)
	{
	case VerticalAlignments::Stretch:
	{

	}
	break;
	case VerticalAlignments::Center:
	{

	}
	break;
	}

	this->m_ActualRect.SetLeft(left);
	this->m_ActualRect.SetTop(top);
	this->m_ActualRect.SetWidth(w);
	this->m_ActualRect.SetHeight(h);
}

void CTextBlock::SetText(const wchar_t* data)
{
	this->m_Text = data;
}

D2D1_SIZE_F CTextBlock::GetSize(float width, float height)
{
	D2D1_SIZE_F sz = { 0 };
	if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
	{
		
	}
	sz.width = width;
	sz.height = height;
	return sz;
}