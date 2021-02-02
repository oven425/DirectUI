#include "pch.h"
#include "CControl.h"
using namespace DirectUI;
using namespace Control;

ID2D1Factory* CControl::m_pD2DFactory = NULL;

void CControl::OnSize(float width, float height, float dpiscale)
{
	this->m_DpiScale = dpiscale;
}

void CControl::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	if (this->m_Visibility == Visibilitys::Collapsed)
	{
		this->DesiredSize.width = this->DesiredSize.height = 0;
	}
	else
	{
		this->DesiredSize = this->GetSize(width, height);
	}
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

CDirectUI_Rect CControl::MappingRenderRect(CDirectUI_Rect actual_rect, D2D1_SIZE_F measure_size)
{
	CDirectUI_Rect rc = CDirectUI_Rect(0,0,actual_rect.GetWidth(), actual_rect.GetHeight());
	switch (this->m_HorizontalAlignment)
	{
	case HorizontalAlignments::Center:
	{
		if (rc.GetWidth() < measure_size.width)
		{
			float offset_x = measure_size.width - rc.GetWidth();
			offset_x = offset_x / 2;
			rc.SetX(offset_x);
		}
	}
	break;
	case HorizontalAlignments::Right:
	{
		if (rc.GetWidth() < measure_size.width)
		{
			float offset_x = measure_size.width - rc.GetWidth();
			rc.SetX(offset_x);
		}
	}
	break;
	}
	switch (this->m_VerticalAlignment)
	{
	case VerticalAlignments::Center:
	{
		if (rc.GetHeight() < measure_size.height)
		{
			float offset_y = measure_size.height - rc.GetHeight();
			offset_y = offset_y / 2;
			rc.SetY(offset_y);
		}
	}
	break;
	case VerticalAlignments::Bottom:
	{
		if (rc.GetHeight() < measure_size.height)
		{
			float offset_y = measure_size.height - rc.GetHeight();
			rc.SetY(offset_y);
		}
	}
	break;
	}
	return rc;
}

void CControl::Arrange(float x, float y, float width, float height)
{
	CDirectUI_Thinkness margin = this->Margin;
	x = x + margin.GetLeft();
	y = y + margin.GetTop();
	width = width - margin.GetLeft() - margin.GetRight();
	height = height - margin.GetTop() - margin.GetBottom();
	D2D1_SIZE_F sz = this->GetSize(width, height);
	float left = x;
	float top = y;
	float right = left + sz.width;
	if (width < sz.width)
	{
		right = left + width;
	}
	float bottom = top + sz.height;
	if (height < sz.height)
	{
		bottom = top + height;
	}
	float w = right - left;
	//if (this->m_HorizontalAlignment != HorizontalAlignments::Stretch)
	{
		if (w > this->DesiredSize.width)
		{
			w = this->DesiredSize.width;
		}
	}
	float h = bottom - top;
	//if (this->m_VerticalAlignment != VerticalAlignments::Stretch)
	{
		if (h > this->DesiredSize.height)
		{
			h = this->DesiredSize.height;
		}
	}
	switch (this->m_HorizontalAlignment)
	{
	case HorizontalAlignments::Stretch:
	{
		//left = left + (width - w) / 2;
		if (width > this->DesiredSize.width)
		{
			left = left + (width - w) / 2;
		}
	}
	break;
	case HorizontalAlignments::Center:
	{
		//w = this->DesiredSize.width;
		left = left + (width - w) / 2;
	}
	break;
	case HorizontalAlignments::Left:
	{
		//w = this->DesiredSize.width;
	}
	break;
	case HorizontalAlignments::Right:
	{
		//w = this->DesiredSize.width;
		left = left + (width - w);
	}
	break;
	}
	switch (this->m_VerticalAlignment)
	{
	case VerticalAlignments::Stretch:
	{
		if (height > this->DesiredSize.height)
		{
			top = top + (height - h) / 2;
		}
	}
	break;
	case VerticalAlignments::Center:
	{
		top = top + (height - h) / 2;
	}
	break;
	
	case VerticalAlignments::Top:
	{
		//h = this->DesiredSize.height;
	}
	break;
	case VerticalAlignments::Bottom:
	{
		//h = this->DesiredSize.height;
		top = top + (height - h);
	}
	break;
	}

	this->m_ActualRect.SetLeft(left);
	this->m_ActualRect.SetTop(top);
	this->m_ActualRect.SetWidth(w);
	this->m_ActualRect.SetHeight(h);
	//this->m_ActualRect = this->m_ActualRect + this->Margin;
	CTrace::WriteLine(L"%s: %s  Desire w:%f h:%f", this->Name.c_str(), this->m_ActualRect.ToString().c_str(), this->DesiredSize.width, this->DesiredSize.height);
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
		//this->Background->Release();
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
