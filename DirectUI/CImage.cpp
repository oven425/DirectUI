#include "pch.h"
#include "CImage.h"
using namespace DirectUI;
using namespace Control;

void CImage::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);
	if (this->m_pD2DBitmap != NULL)
	{
		if (this->m_Stretch == Stretchs::None)
		{
			this->m_pRenderBuf->DrawBitmap(this->m_pD2DBitmap, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height));
		}
		else
		{
			this->m_pRenderBuf->DrawBitmap(this->m_pD2DBitmap, D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
		}
	}
	
	::CControl::OnRender(pRT);
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
	//CDirectUI_Thinkness margin = this->Margin * this->m_DpiScale;
	CDirectUI_Thinkness margin = this->m_Margin;
	//width = width - margin.GetLeft() - margin.GetRight();
	//height = height - margin.GetTop() - margin.GetBottom();

	CDirectUI_Size sz = data + this->m_Margin;
	//float w = width;
	//float h = height;

	if (this->m_Width > 0)
	{
		//w = this->m_Width;
		sz.SetWidth(this->m_Width);
	}
	if (this->m_Height > 0)
	{
		//h = this->m_Height;
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
			//w = ss.width;
			//h = ss.height;
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
			//dst.right = w;
			//dst.bottom = h;
			D2D1_RECT_F rrc = Calculate_Uniform(src, dst);
			this->DesiredSize.width = rrc.right - rrc.left;
			this->DesiredSize.height = rrc.bottom - rrc.top;
		}
		break;
		case Stretchs::Fill:
		{
			//this->DesiredSize.width = w;
			//this->DesiredSize.height = h;
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
			//dst.right = w;
			//dst.bottom = h;
			D2D1_RECT_F rrc = Calculate_UniformToFill(src, dst);
			this->DesiredSize.width = rrc.right - rrc.left;
			this->DesiredSize.height = rrc.bottom - rrc.top;
		}
		break;
		}
	}
	else
	{
		//this->DesiredSize.width = width;
		//this->DesiredSize.height = height;
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


//void CImage::Measure(float width, float height, ID2D1RenderTarget* pRT)
//{
//	this->DesiredSize.width = this->DesiredSize.height = 0;
//	//CDirectUI_Thinkness margin = this->Margin * this->m_DpiScale;
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
//	
//	if (this->m_pD2DBitmap == NULL)
//	{
//		D2D1_BITMAP_PROPERTIES pp = D2D1_BITMAP_PROPERTIES();
//		pp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
//		pp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
//		double dpix = 0;
//		double dpiy = 0;
//		(*this->m_Source).operator IWICFormatConverter*()->GetResolution(&dpix, &dpiy);
//		pp.dpiX = dpix;
//		pp.dpiY = dpiy;
//		pRT->CreateBitmapFromWicBitmap(*this->m_Source, pp, &this->m_pD2DBitmap);
//	}
//	if (this->m_Source && this->m_pD2DBitmap != NULL)
//	{
//		D2D1_SIZE_F ss = this->m_pD2DBitmap->GetSize();
//		if (w == 0 && h == 0)
//		{
//			w = ss.width;
//			h = ss.height;
//		}
//		else if (w == 0)
//		{
//			float h_ = h / ss.height;
//			w = ss.width * h_;
//		}
//		else if (h == 0)
//		{
//			float w_ = w / ss.width;
//			h = ss.height * w_;
//		}
//		switch (this->m_Stretch)
//		{
//		case Stretchs::Uniform:
//		{
//			D2D1_RECT_F src = { 0 };
//			src.right = ss.width;
//			src.bottom = ss.height;
//			D2D1_RECT_F dst = { 0 };
//			dst.right = w;
//			dst.bottom = h;
//			D2D1_RECT_F rrc = Calculate_Uniform(src, dst);
//			this->DesiredSize.width = rrc.right - rrc.left;
//			this->DesiredSize.height = rrc.bottom - rrc.top;
//		}
//		break;
//		case Stretchs::Fill:
//		{
//			this->DesiredSize.width = w;
//			this->DesiredSize.height = h;
//		}
//		break;
//		case Stretchs::None:
//		{
//			D2D1_SIZE_F ss = this->m_pD2DBitmap->GetSize();
//			if (this->m_Width > 0)
//			{
//				if (this->m_Width < this->DesiredSize.width)
//				{
//					this->DesiredSize.width = this->m_Width;
//				}
//				else
//				{
//					this->DesiredSize.width = ss.width;
//				}
//			}
//			else
//			{
//				this->DesiredSize.width = ss.width;
//			}
//			if (this->m_Height > 0)
//			{
//				if (ss.height < this->m_Height)
//				{
//					this->DesiredSize.height =ss.height;
//				}
//				else
//				{
//					this->DesiredSize.height = this->m_Height;
//				}
//				
//			}
//			else
//			{
//				this->DesiredSize.height = ss.height;
//			}
//		}
//		break;
//		case Stretchs::UniformToFill:
//		{
//			D2D1_RECT_F src = { 0 };
//			src.right = ss.width;
//			src.bottom = ss.height;
//			D2D1_RECT_F dst = { 0 };
//			dst.right = w;
//			dst.bottom = h;
//			D2D1_RECT_F rrc = Calculate_UniformToFill(src, dst);
//			this->DesiredSize.width = rrc.right - rrc.left;
//			this->DesiredSize.height = rrc.bottom - rrc.top;
//		}
//		break;
//		}
//	}
//	else
//	{
//		this->DesiredSize.width = width;
//		this->DesiredSize.height = height;
//	}
//	if (this->DesiredSize.width < 0)
//	{
//		this->DesiredSize.width = 0;
//	}
//	if (this->DesiredSize.height < 0)
//	{
//		this->DesiredSize.height = 0;
//	}
//}

//D2D1_SIZE_F CImage::GetSize(float width, float height)
//{
//	//D2D1_SIZE_F sz = { 0 };
//	//sz.width = this->DesiredSize.width;
//	//sz.height = this->DesiredSize.height;
//
//	//return sz;
//
//	return ::CControl::GetSize(width, height);
//}

//void CImage::Arrange(float x, float y, float width, float height)
//{
//	::CControl::Arrange(x, y, width, height);
//}

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