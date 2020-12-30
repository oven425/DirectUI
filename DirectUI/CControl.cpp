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
	//float left = x+ this->Margin.GetLeft();
	//float top = y + this->Margin.GetTop();
	//float right = x + width - this->Margin.GetRight();
	//float bottom = y + height - this->Margin.GetBottom();
	D2D1_SIZE_F sz = this->GetSize(width, height);
	float left = x;
	float top = y;
	float right = x + sz.width;
	float bottom = y + sz.height;
	float w = right - left;
	float h = bottom - top;
	//if (w != this->DesiredSize.width)
	{
		switch (this->GetHorizontalAlignment())
		{
		case HorizontalAlignments::Stretch:
		{
			//w = this->DesiredSize.width;
		}
		break;
		case HorizontalAlignments::Left:
		{
			w = this->DesiredSize.width;
		}
		break;
		case HorizontalAlignments::Center:
		{
			left = left + (w - this->DesiredSize.width) / 2;
			w = this->DesiredSize.width;
		}
		break;
		case HorizontalAlignments::Right:
		{
			left = left + (w - this->DesiredSize.width);
			w = this->DesiredSize.width;
		}
		break;
		}
		
	}
	
	//if (h != this->DesiredSize.height)
	{
		switch (this->GetVerticalAlignment())
		{
		case VerticalAlignments::Stretch:
		{
			//h = this->DesiredSize.height;
		}
		break;
		case VerticalAlignments::Top:
		{
			h = this->DesiredSize.height;
		}
		break;
		case VerticalAlignments::Center:
		{
			top = top + (h - this->DesiredSize.height) / 2;
			h = this->DesiredSize.height;
		}
		break;
		case VerticalAlignments::Bottom:
		{
			top = top + (h - this->DesiredSize.height);
			h = this->DesiredSize.height;
		}
		break;
		}
		
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
}

void CControl::OnRender(ID2D1HwndRenderTarget* pRT)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	HRESULT hr = pRT->CreateCompatibleRenderTarget(D2D1::SizeF(this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight()), &pCompatibleRenderTarget);
	CDirectUI_Rect rc = (this->m_ActualRect) / this->m_DpiScale;
	if (this->Background)
	{
		this->Background->Refresh(pRT);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
		pRT->FillRectangle(rc, m_pBlackBrush);
		//pCompatibleRenderTarget->FillRectangle(rc, m_pBlackBrush);
	}
	//ID2D1Bitmap* bmp = NULL;
	//pCompatibleRenderTarget->GetBitmap(&bmp);
	//pRT->DrawBitmap(bmp);
	pCompatibleRenderTarget->Release();
}

void CControl::Release()
{
	if (this->m_pBmpRT != NULL)
	{
		this->m_pBmpRT->Release();
		this->m_pBmpRT = NULL;
	}
}
