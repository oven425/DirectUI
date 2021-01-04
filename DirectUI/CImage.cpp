#include "pch.h"
#include "CImage.h"
using namespace DirectUI;
using namespace Control;

void CImage::OnRender(ID2D1RenderTarget* pRT)
{
	//::CControl::OnRender(pRT);
	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);
	pCompatibleRenderTarget->BeginDraw();
	if (this->m_pD2DBitmap == NULL)
	{
		pCompatibleRenderTarget->CreateBitmapFromWicBitmap(*this->m_Source, NULL, &this->m_pD2DBitmap);
	}
	if (this->m_pD2DBitmap != NULL)
	{
		pCompatibleRenderTarget->DrawBitmap(this->m_pD2DBitmap);
	}

	pCompatibleRenderTarget->EndDraw();
	ID2D1Bitmap* bmp = NULL;
	pCompatibleRenderTarget->GetBitmap(&bmp);

	CDirectUI_Rect rc_dst = this->m_ActualRect / (this->m_DpiScale*3);
	CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);


	bmp->Release();
	pCompatibleRenderTarget->Release();
}

void CImage::Measure(float width, float height)
{
	if (this->m_Source && this->m_Source->operator IWICFormatConverter*()!=NULL)
	{
		switch (this->m_Stretch)
		{
		case Stretchs::Uniform:
		{

		}
		break;
		case Stretchs::Fill:
		{
			this->DesiredSize.width = width;
			this->DesiredSize.height = height;
		}
		break;
		case Stretchs::None:
		{
			this->DesiredSize.width = this->m_Source->GetWidth();
			this->DesiredSize.height = this->m_Source->GetHeight();
		}
		break;
		case Stretchs::UniformToFill:
		{

		}
		break;
		}
	}
	else
	{
		this->DesiredSize.width = width;
		this->DesiredSize.height = height;
	}
}

void CImage::Arrange(float x, float y, float width, float height)
{
	float left = x;
	float top = y;
	float right = x + width;
	float bottom = y + height;
	float w = right - left;
	float h = bottom - top;
	switch (this->m_HorizontalAlignment)
	{
	case HorizontalAlignments::Stretch:
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
	case HorizontalAlignments::Left:
	{

	}
	break;
	case HorizontalAlignments::Right:
	{

	}
	break;
	}

	switch (this->m_VerticalAlignment)
	{
	case VerticalAlignments::Stretch:
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
	case VerticalAlignments::Top:
	{

	}
	break;
	case VerticalAlignments::Bottom:
	{

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

}

void CImage::SetSource(shared_ptr<CImageSource> data)
{
	if (this->m_pD2DBitmap != NULL)
	{
		this->m_pD2DBitmap->Release();
		this->m_pD2DBitmap = NULL;
	}
	this->m_Source = data;
}

void CImage::SetStretch(Stretchs data)
{
	this->m_Stretch = data;
}