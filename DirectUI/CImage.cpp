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
	//if (this->m_pD2DBitmap == NULL)
	//{
	//	//D2D1_BITMAP_PROPERTIES pp = D2D1_BITMAP_PROPERTIES();
	//	//pp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//	//pp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	//	//pp.dpiX = this->m_Source->GetHeight;
	//	//pp.dpiY = 299;
	//	pCompatibleRenderTarget->CreateBitmapFromWicBitmap(*this->m_Source, NULL, &this->m_pD2DBitmap);
	//}
	if (this->m_pD2DBitmap != NULL)
	{
		if (this->m_Stretch == Stretchs::None)
		{
			pCompatibleRenderTarget->DrawBitmap(this->m_pD2DBitmap, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height));
		}
		else
		{
			pCompatibleRenderTarget->DrawBitmap(this->m_pD2DBitmap, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height));
		}
	}

	pCompatibleRenderTarget->EndDraw();
	ID2D1Bitmap* bmp = NULL;
	pCompatibleRenderTarget->GetBitmap(&bmp);

	CDirectUI_Rect rc_dst = this->m_ActualRect / (this->m_DpiScale);
	CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);


	bmp->Release();
	pCompatibleRenderTarget->Release();
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

D2D1_RECT_F CImage::LetterBoxRect(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst)
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

void CImage::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
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
		if (w == 0)
		{
			float h_ = h / ss.height;
			w = ss.width * h_;
		}
		if (h == 0)
		{
			float w_ = w / ss.width;
			h = ss.height * w_;
		}
		switch (this->m_Stretch)
		{
		case Stretchs::Uniform:
		{
			D2D1_RECT_F src = { 0 };
			src.right = ss.width;
			src.bottom = ss.height;
			D2D1_RECT_F dst = { 0 };
			dst.right = w;
			dst.bottom = h;
			D2D1_RECT_F rrc = LetterBoxRect(src, dst);
			this->DesiredSize.width = rrc.right - rrc.left;
			this->DesiredSize.height = rrc.bottom - rrc.top;
		}
		break;
		case Stretchs::Fill:
		{
			this->DesiredSize.width = w;
			this->DesiredSize.height = h;
		}
		break;
		case Stretchs::None:
		{
			D2D1_SIZE_F ss = this->m_pD2DBitmap->GetSize();
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
			//if (h == 0)
			//{
			//	this->DesiredSize.height = ss.height;
			//}
			//else
			//{
			//	this->DesiredSize.height = ss.height < h ? ss.height : h;
			//}
			//if (w == 0)
			//{
			//	this->DesiredSize.width = ss.width;
			//}
			//else
			//{
			//	this->DesiredSize.width = ss.width < w ? ss.width : w;
			//}
			this->DesiredSize.width = ss.width;
			this->DesiredSize.height = ss.height;
		}
		break;
		case Stretchs::UniformToFill:
		{
			D2D1_RECT_F src = { 0 };
			src.right = ss.width;
			src.bottom = ss.height;
			D2D1_RECT_F dst = { 0 };
			dst.right = w;
			dst.bottom = h;
			D2D1_RECT_F rrc = LetterBoxRect(src, dst);
			this->DesiredSize.width = rrc.right - rrc.left;
			this->DesiredSize.height = rrc.bottom - rrc.top;
			//D2D1_SIZE_F ss = this->m_pD2DBitmap->GetSize();
			//float ww = ss.width*height;
			//float hh = ss.height*width;
			//CTrace::WriteLine(L"ww:%f hh:%f", ww, hh);
			//if (height > width)
			//{
			//	this->DesiredSize.height = height;
			//	float w = height / ss.height;
			//	this->DesiredSize.width = w * width;
			//}
			//else
			//{
			//	this->DesiredSize.width = width;
			//	float h = width / ss.width;
			//	this->DesiredSize.height = h * height;
			//}
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

D2D1_SIZE_F CImage::GetSize(float width, float height)
{
	D2D1_SIZE_F sz = { 0 };
	sz.width = this->DesiredSize.width;
	sz.height = this->DesiredSize.height;

	return sz;
	//return CControl::GetSize(width, height);
}

void CImage::Arrange(float x, float y, float width, float height)
{
	::CControl::Arrange(x, y, width, height);
	//float left = x;
	//float top = y;
	//float right = x + width;
	//float bottom = y + height;
	//float w = right - left;
	//float h = bottom - top;
	//switch (this->m_HorizontalAlignment)
	//{
	//case HorizontalAlignments::Stretch:
	//{
	//	::CControl::Arrange(x, y, width, height);
	//}
	//break;
	//case HorizontalAlignments::Center:
	//{
	//	float w1 = this->DesiredSize.width;
	//	if (w1 > width)
	//	{
	//		w1 = width;
	//	}
	//	left = left + (w - w1) / 2;
	//	w = w1;
	//}
	//break;
	//case HorizontalAlignments::Left:
	//{

	//}
	//break;
	//case HorizontalAlignments::Right:
	//{

	//}
	//break;
	//}

	//switch (this->m_VerticalAlignment)
	//{
	//case VerticalAlignments::Stretch:
	//case VerticalAlignments::Center:
	//{
	//	float h1 = this->DesiredSize.height;
	//	if (h1 > height)
	//	{
	//		h1 = height;
	//	}
	//	top = top + (h - h1) / 2;
	//	h = h1;
	//}
	//break;
	//case VerticalAlignments::Top:
	//{

	//}
	//break;
	//case VerticalAlignments::Bottom:
	//{

	//}
	//break;
	//}

	//if (left < 0 && this->m_HorizontalAlignment == HorizontalAlignments::Left)
	//{
	//	left = 0;
	//}
	//if (top < 0 && this->m_VerticalAlignment == VerticalAlignments::Top)
	//{
	//	top = 0;
	//}
	////left = left + this->Margin.GetLeft();
	////top = top + this->Margin.GetTop();

	//this->m_ActualRect.SetX(left);
	//this->m_ActualRect.SetY(top);
	//this->m_ActualRect.SetWidth(w);
	//this->m_ActualRect.SetHeight(h);
	////this->m_ActualRect = this->m_ActualRect + this->Margin;
	//CTrace::WriteLine(L"%s: %s  Desire w:%f h:%f", this->Name.c_str(), this->m_ActualRect.ToString().c_str(), this->DesiredSize.width, this->DesiredSize.height);

}

void CImage::SetSource(shared_ptr<CD2D_ImageSource> data)
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