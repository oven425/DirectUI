#include "pch.h"
#include "CImage.h"
using namespace DirectUI;
using namespace Control;

CDirectUI_Rect CImage::MappingToSource(CDirectUI_Rect& actual_rect, const CDirectUI_Size& measure_size, bool ignore_x, bool ignore_y)
{
	CDirectUI_Rect rc = CDirectUI_Rect(0,0, actual_rect.GetWidth(), actual_rect.GetHeight());
	if (ignore_x == false)
	{
		switch (this->m_HorizontalAlignment)
		{
		case HorizontalAlignments::Center:
		{
			if (rc.GetWidth() < measure_size.GetWidth())
			{
				float offset_x = measure_size.GetWidth() - rc.GetWidth();
				offset_x = offset_x / 2;
				//rc.SetX(offset_x);
				rc.SetOffsetX(offset_x);
			}
		}
		break;
		case HorizontalAlignments::Right:
		{
			if (rc.GetWidth() < measure_size.GetWidth())
			{
				float offset_x = measure_size.GetWidth() - rc.GetWidth();
				//CTrace::WriteLine(L"offset_x:%f", offset_x);
				//rc.SetOffsetX(offset_x);
				rc.SetX(abs(offset_x));
			}
		}
		break;
		}
	}
	if (ignore_y == false)
	{
		switch (this->m_VerticalAlignment)
		{
		case VerticalAlignments::Center:
		{
			if (rc.GetHeight() < measure_size.GetHeight())
			{
				float offset_y = measure_size.GetHeight() - rc.GetHeight();
				offset_y = offset_y / 2;
				rc.SetY(offset_y);
			}
		}
		break;
		case VerticalAlignments::Bottom:
		{
			if (rc.GetHeight() < measure_size.GetHeight())
			{
				float offset_y = measure_size.GetHeight() - rc.GetHeight();
				rc.SetY(offset_y);
			}
		}
		break;
		}
	}

	return rc;
}


void CImage::OnRender(ID2D1RenderTarget* pRT)
{
	//this->CreateRenderBuf(pRT, this->DesiredSize);
	//if (this->m_pD2DBitmap != NULL)
	//{
	//	if (this->m_Stretch == Stretchs::None)
	//	{
	//		this->m_pRenderBuf->DrawBitmap(this->m_pD2DBitmap, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height));
	//	}
	//	else
	//	{
	//		this->m_pRenderBuf->DrawBitmap(this->m_pD2DBitmap, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	//	}
	//}
	//
	//::CControl::OnRender(pRT);

	//pRT->PushAxisAlignedClip(this->m_ActualRect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	//if (this->m_pD2DBitmap != NULL)
	//{
	//	CDirectUI_Rect rc = this->MappingToSource(this->m_ActualRect, this->DesiredSize);
	//	//CDirectUI_Rect rc1 = this->m_ActualRect;
	//	//rc1.SetX(abs(rc.GetLeft()));
	//	//rc1.SetY(abs(rc.GetTop()));
	//	if (this->m_Stretch == Stretchs::None)
	//	{
	//		pRT->DrawBitmap(this->m_pD2DBitmap, this->m_ActualRect, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc);
	//	}
	//	else
	//	{
	//		pRT->DrawBitmap(this->m_pD2DBitmap, this->m_ActualRect, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	//	}
	//}
	//pRT->PopAxisAlignedClip();

	pRT->PushAxisAlignedClip(this->m_ActualRect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	if (this->m_pD2DBitmap != NULL)
	{
		pRT->DrawBitmap(this->m_pD2DBitmap, this->m_MeasureRect, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	}
	pRT->PopAxisAlignedClip();
}

D2D1_RECT_F CImage::Calculate_Uniform(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst)
{
	D2D1_RECT_F rc = { 0 };
	float iSrcWidth = rcSrc.right - rcSrc.left;
	float iSrcHeight = rcSrc.bottom - rcSrc.top;

	float iDstWidth = rcDst.right - rcDst.left;
	float iDstHeight = rcDst.bottom - rcDst.top;

	float iDstLBWidth = 0;
	float iDstLBHeight = 0;
	if (iDstWidth == 0 && iDstHeight == 0)
	{

	}
	else if (iDstWidth == 0)
	{
		float h_ = iDstHeight / iSrcHeight;
		iDstLBWidth = iDstWidth * h_;
		iDstLBHeight = iSrcHeight;
	}
	else if (iDstHeight == 0)
	{
		float w_ = iDstWidth / iSrcWidth;
		iDstLBWidth = iDstWidth;
		iDstLBHeight = iSrcHeight * w_;
	}
	else
	{
		if (MulDiv(iSrcWidth, iDstHeight, iSrcHeight) <= iDstWidth)
		{
			// Column letterboxing ("pillar box")
			iDstLBWidth = MulDiv(iDstHeight, iSrcWidth, iSrcHeight);
			iDstLBHeight = iDstHeight;
		}
		else
		{
			// Row letterboxing.
			iDstLBWidth = iDstWidth;
			iDstLBHeight = MulDiv(iDstWidth, iSrcHeight, iSrcWidth);
		}
	}
	float left = rcDst.left + ((iDstWidth - iDstLBWidth) / 2);
	float top = rcDst.top + ((iDstHeight - iDstLBHeight) / 2);
	rc.left = left;
	rc.top = top;
	rc.right = left + iDstLBWidth;
	rc.bottom = top + iDstLBHeight;
	return rc;
}

D2D1_RECT_F CImage::Calculate_UniformToFill(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst)
{
	D2D1_RECT_F rc = { 0 };
	float iSrcWidth = rcSrc.right - rcSrc.left;
	float iSrcHeight = rcSrc.bottom - rcSrc.top;

	float iDstWidth = rcDst.right - rcDst.left;
	float iDstHeight = rcDst.bottom - rcDst.top;

	float iDstLBWidth = 0;
	float iDstLBHeight = 0;
	if (iDstWidth == 0 && iDstHeight == 0)
	{

	}
	else if (iDstWidth == 0)
	{
		float h_ = iDstHeight / iSrcHeight;
		iDstLBWidth = iDstWidth * h_;
		iDstLBHeight = iSrcHeight;
	}
	else if (iDstHeight == 0)
	{
		float w_ = iDstWidth / iSrcWidth;
		iDstLBWidth = iDstWidth;
		iDstLBHeight = iSrcHeight * w_;
	}
	else
	{
		if (MulDiv(iSrcWidth, iDstHeight, iSrcHeight) >= iDstWidth)
		{
			// Column letterboxing ("pillar box")
			iDstLBWidth = MulDiv(iDstHeight, iSrcWidth, iSrcHeight);
			iDstLBHeight = iDstHeight;
		}
		else
		{
			// Row letterboxing.
			iDstLBWidth = iDstWidth;
			iDstLBHeight = MulDiv(iDstWidth, iSrcHeight, iSrcWidth);
		}
	}
	float left = rcDst.left + ((iDstWidth - iDstLBWidth) / 2);
	float top = rcDst.top + ((iDstHeight - iDstLBHeight) / 2);
	rc.left = left;
	rc.top = top;
	rc.right = left + iDstLBWidth;
	rc.bottom = top + iDstLBHeight;
	return rc;
}

void CImage::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Thinkness margin = *this->Margin;


	CDirectUI_Size sz = data + *this->Margin;

	if (this->m_Width > 0)
	{
		sz.SetWidth(this->m_Width);
	}
	if (this->m_Height > 0)
	{
		sz.SetHeight(this->m_Height);
	}

	if (this->m_pD2DBitmap == NULL)
	{
		D2D1_BITMAP_PROPERTIES pp = D2D1_BITMAP_PROPERTIES();
		pp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
		pp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		double dpix = 0;
		double dpiy = 0;
		(*this->m_Source).operator IWICFormatConverter*()->GetResolution(&dpix, &dpiy);
		pp.dpiX = dpix;
		pp.dpiY = dpiy;
		pRT->CreateBitmapFromWicBitmap(*this->m_Source, pp, &this->m_pD2DBitmap);
	}
	if (this->m_Source && this->m_pD2DBitmap != NULL)
	{
		D2D1_SIZE_F ss = this->m_pD2DBitmap->GetSize();
		if (sz == 0)
		{
			sz = ss;
		}
		else if (sz.GetWidth() == 0)
		{
			float h_ = sz.GetHeight() / ss.height;
			sz.SetWidth(ss.width * h_);
		}
		else if (sz.GetHeight() == 0)
		{
			float w_ = sz.GetWidth() / ss.width;
			sz.SetHeight(ss.height * w_);
		}
		switch (this->m_Stretch)
		{
		case Stretchs::Uniform:
		{
			D2D1_RECT_F src = { 0 };
			src.right = ss.width;
			src.bottom = ss.height;
			D2D1_RECT_F dst = sz;
			D2D1_RECT_F rrc = Calculate_Uniform(src, dst);
			this->DesiredSize.width = rrc.right - rrc.left;
			this->DesiredSize.height = rrc.bottom - rrc.top;
		}
		break;
		case Stretchs::Fill:
		{
			this->DesiredSize = sz;
		}
		break;
		case Stretchs::None:
		{
			D2D1_SIZE_F ss = this->m_pD2DBitmap->GetSize();
			if (this->m_Width > 0)
			{
				if (this->m_Width < this->DesiredSize.width)
				{
					this->DesiredSize.width = this->m_Width;
				}
				else
				{
					this->DesiredSize.width = ss.width;
				}
			}
			else
			{
				this->DesiredSize.width = ss.width;
			}
			if (this->m_Height > 0)
			{
				if (ss.height < this->m_Height)
				{
					this->DesiredSize.height = ss.height;
				}
				else
				{
					this->DesiredSize.height = this->m_Height;
				}

			}
			else
			{
				this->DesiredSize.height = ss.height;
			}
		}
		break;
		case Stretchs::UniformToFill:
		{
			D2D1_RECT_F src = { 0 };
			src.right = ss.width;
			src.bottom = ss.height;
			D2D1_RECT_F dst = sz;
			D2D1_RECT_F rrc = Calculate_UniformToFill(src, dst);
			this->DesiredSize.width = rrc.right - rrc.left;
			this->DesiredSize.height = rrc.bottom - rrc.top;
		}
		break;
		}
	}
	else
	{
		this->DesiredSize = data;
	}
	if (this->DesiredSize.width < 0)
	{
		this->DesiredSize.width = 0;
	}
	if (this->DesiredSize.height < 0)
	{
		this->DesiredSize.height = 0;
	}
}

void CImage::Measure(const CDirectUI_Rect& data, ID2D1RenderTarget* pRT)
{
	this->m_MeasureRect = 0;

	CDirectUI_Rect rc = data + *this->Margin;
	CDirectUI_Size sz = rc;
	if (this->m_Width > 0)
	{
		sz.SetWidth(this->m_Width);
	}
	if (this->m_Height > 0)
	{
		sz.SetHeight(this->m_Height);
	}

	if (this->m_pD2DBitmap == NULL)
	{
		D2D1_BITMAP_PROPERTIES pp = D2D1_BITMAP_PROPERTIES();
		pp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
		pp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		double dpix = 0;
		double dpiy = 0;
		(*this->m_Source).operator IWICFormatConverter*()->GetResolution(&dpix, &dpiy);
		pp.dpiX = dpix;
		pp.dpiY = dpiy;
		pRT->CreateBitmapFromWicBitmap(*this->m_Source, pp, &this->m_pD2DBitmap);
	}
	if (this->m_Source && this->m_pD2DBitmap != NULL)
	{
		D2D1_SIZE_F ss = this->m_pD2DBitmap->GetSize();
		if (sz == 0)
		{
			sz = ss;
		}
		else if (sz.GetWidth() == 0)
		{
			float h_ = sz.GetHeight() / ss.height;
			sz.SetWidth(ss.width * h_);
		}
		else if (sz.GetHeight() == 0)
		{
			float w_ = sz.GetWidth() / ss.width;
			sz.SetHeight(ss.height * w_);
		}
		switch (this->m_Stretch)
		{
		case Stretchs::Uniform:
		{
			D2D1_RECT_F src = { 0 };
			src.right = ss.width;
			src.bottom = ss.height;
			D2D1_RECT_F dst = sz;
			D2D1_RECT_F rrc = Calculate_Uniform(src, dst);
			this->DesiredSize.width = rrc.right - rrc.left;
			this->DesiredSize.height = rrc.bottom - rrc.top;
		}
		break;
		case Stretchs::Fill:
		{
			this->DesiredSize = sz;
		}
		break;
		case Stretchs::None:
		{
			D2D1_SIZE_F ss = this->m_pD2DBitmap->GetSize();
			if (this->m_Width > 0)
			{
				if (this->m_Width < this->DesiredSize.width)
				{
					this->DesiredSize.width = this->m_Width;
				}
				else
				{
					this->DesiredSize.width = ss.width;
				}
			}
			else
			{
				this->DesiredSize.width = ss.width;
			}
			if (this->m_Height > 0)
			{
				if (ss.height < this->m_Height)
				{
					this->DesiredSize.height = ss.height;
				}
				else
				{
					this->DesiredSize.height = this->m_Height;
				}

			}
			else
			{
				this->DesiredSize.height = ss.height;
			}
		}
		break;
		case Stretchs::UniformToFill:
		{
			D2D1_RECT_F src = { 0 };
			src.right = ss.width;
			src.bottom = ss.height;
			D2D1_RECT_F dst = sz;
			D2D1_RECT_F rrc = Calculate_UniformToFill(src, dst);
			this->DesiredSize.width = rrc.right - rrc.left;
			this->DesiredSize.height = rrc.bottom - rrc.top;
		}
		break;
		}
	}
	else
	{
		this->DesiredSize = data;
	}
	//if (this->DesiredSize.width < 0)
	//{
	//	this->DesiredSize.width = 0;
	//}
	//if (this->DesiredSize.height < 0)
	//{
	//	this->DesiredSize.height = 0;
	//}
	this->m_MeasureRect = ::UIElement::MeasureMapping(rc, this->DesiredSize, this->m_HorizontalAlignment, this->m_VerticalAlignment);
}

void CImage::Arrange(const CDirectUI_Rect& data)
{
	::CControl::Arrange(data);
}

void CImage::SetSource(shared_ptr<Direct2D::CD2D_ImageSource> data)
{
	this->Release();
	this->m_Source = data;
}

void CImage::SetStretch(Stretchs data)
{
	this->m_Stretch = data;
}

void CImage::Release()
{
	if (this->m_pD2DBitmap != NULL)
	{
		this->m_pD2DBitmap->Release();
		this->m_pD2DBitmap = NULL;
	}
}