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
	//this->DesiredSize.width = width;
	//if (this->m_Width > 0)
	//{
	//	if (width < this->m_Width)
	//	{
	//		this->DesiredSize.width = width;
	//	}
	//	else
	//	{
	//		this->DesiredSize.width = this->m_Width;
	//	}
	//	this->DesiredSize.width = this->m_Width;
	//}
	//this->DesiredSize.height = height;
	//if (this->m_Height > 0)
	//{
	//	if (height < this->m_Height)
	//	{
	//		this->DesiredSize.height = height;
	//	}
	//	else
	//	{
	//		this->DesiredSize.height = this->m_Height;
	//	}
	//	this->DesiredSize.height = this->m_Height;
	//}
	//this->DesiredSize.width = this->DesiredSize.width - this->Margin.GetLeft() - this->Margin.GetRight();
	//this->DesiredSize.height = this->DesiredSize.height - this->Margin.GetTop() - this->Margin.GetBottom();
	this->DesiredSize = this->GetSize(width, height);
}

D2D1_SIZE_F CControl::GetSize(float width, float height)
{
	D2D1_SIZE_F sz = { 0 };
	sz.width = width;
	sz.height = height;
	if (this->m_Width > 0)
	{
		sz.width = this->m_Width;
	}
	if (this->m_Height > 0)
	{
		sz.height = this->m_Height;
	}
	return sz;
}

void CControl::Arrange(float x, float y, float width, float height)
{
	D2D1_SIZE_F sz = this->GetSize(width, height);
	if (sz.width > width)
	{
		sz.width = width;
	}
	if (sz.height > height)
	{
		sz.height = height;
	}
	float left = x;
	float top = y;
	float right = x + sz.width;
	float bottom = y + sz.height;
	float w = right - left;
	float h = bottom - top;
	switch (this->m_HorizontalAlignment)
	{
	case HorizontalAlignments::Stretch:
	{
		
	}
	break;
	case HorizontalAlignments::Left:
	{
		w = this->DesiredSize.width;
		if (w > width)
		{
			w = width;
		}
	}
	break;
	case HorizontalAlignments::Center:
	{
		float w1 = this->DesiredSize.width;
		if (w1 > width)
		{
			w1 = width;
		}
		left = left + (w - w1) / 2;
		w = w1;
	}
	break;
	case HorizontalAlignments::Right:
	{
		float w1 = this->DesiredSize.width;
		if (w1 > width)
		{
			w1 = width;
		}
		left = left + (w - w1);
		w = w1;
	}
	break;
	}
	
	switch (this->m_VerticalAlignment)
	{
	case VerticalAlignments::Stretch:
	{
		//h = this->DesiredSize.height;
	}
	break;
	case VerticalAlignments::Top:
	{
		h = this->DesiredSize.height;
		if (h > height)
		{
			h = height;
		}
	}
	break;
	case VerticalAlignments::Center:
	{
		float h1 = this->DesiredSize.height;
		if (h1 > height)
		{
			h1 = height;
		}
		top = top + (h - h1) / 2;
		h = h1;
	}
	break;
	case VerticalAlignments::Bottom:
	{
		float h1 = this->DesiredSize.height;
		if (h1 > height)
		{
			h1 = height;
		}
		top = top + (h - h1);
		h = h1;
	}
	break;
	}
	if (left < 0 && this->m_HorizontalAlignment == HorizontalAlignments::Left)
	{
		left = 0;
	}
	if (top < 0 && this->m_VerticalAlignment == VerticalAlignments::Top)
	{
		top = 0;
	}
	//left = left + this->Margin.GetLeft();
	//top = top + this->Margin.GetTop();

	this->m_ActualRect.SetX(left);
	this->m_ActualRect.SetY(top);
	this->m_ActualRect.SetWidth(w);
	this->m_ActualRect.SetHeight(h);
	//this->m_ActualRect = this->m_ActualRect + this->Margin;
	CTrace::WriteLine(L"%s: %s  Desire w:%f h:%f", this->Name.c_str(), this->m_ActualRect.ToString().c_str(), this->DesiredSize.width, this->DesiredSize.height);


	
	//::OutputDebugStringW(this->m_ActualRect.ToString().c_str());
	//::OutputDebugStringW(L"\r\n");
}

#define Test
void CControl::OnRender(ID2D1RenderTarget* pRT)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
#ifdef  Test
	HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);
#else
	HRESULT hr = pRT->CreateCompatibleRenderTarget(D2D1::SizeF(this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight()), &pCompatibleRenderTarget);
#endif //  Test

	
	pCompatibleRenderTarget->BeginDraw();
	
	if (this->Background)
	{
		this->Background->Release();
		this->Background->Refresh(pCompatibleRenderTarget);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
#ifdef Test
		CDirectUI_Rect rc(0,0, this->DesiredSize.width, this->DesiredSize.height);
		pCompatibleRenderTarget->FillRectangle(rc, m_pBlackBrush);
#else
		CDirectUI_Rect rc = (this->m_ActualRect) / this->m_DpiScale;
		pCompatibleRenderTarget->FillRectangle(rc, m_pBlackBrush);
#endif
		
	}
	pCompatibleRenderTarget->EndDraw();
	ID2D1Bitmap* bmp = NULL;
	pCompatibleRenderTarget->GetBitmap(&bmp);
#ifdef Test
	CDirectUI_Rect rc_dst = this->m_ActualRect/this->m_DpiScale;
	CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);
#else
	pRT->DrawBitmap(bmp);
#endif
	
	bmp->Release();
	pCompatibleRenderTarget->Release();
}
