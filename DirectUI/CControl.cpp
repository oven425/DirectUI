#include "pch.h"
#include "CControl.h"
using namespace DirectUI;
using namespace Control;

ID2D1Factory* CControl::m_pD2DFactory = NULL;
CDependencyObject<shared_ptr<CControl>, shared_ptr<CControl>> CControl::m_Parent;

bool CControl::HitTest(int x, int y, vector<shared_ptr<CControl>>& childs)
{
	bool result = false;
	//shared_ptr<CControl> result;
	if (this->m_Visibility == Visibilitys::Visible && this->m_ActualRect.PtInRect(x, y) == true)
	{
		childs.push_back(this->shared_from_this());
		result = true;
	}

	return result;
}

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
		//this->DesiredSize.width = this->DesiredSize.height = 0;
		//CDirectUI_Thinkness margin = this->m_Margin;
		//width = width - margin.GetLeft() - margin.GetRight();
		//height = height - margin.GetTop() - margin.GetBottom();
		//float w = width;
		//float h = height;

		//if (this->m_Width > 0)
		//{
		//	w = this->m_Width;
		//}
		//if (this->m_Height > 0)
		//{
		//	h = this->m_Height;
		//}
		//this->DesiredSize = this->GetSize(w, h);
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

CDirectUI_Rect CControl::MappingRenderRect(CDirectUI_Rect& actual_rect, D2D1_SIZE_F& measure_size, bool ignore_x, bool ignore_y)
{
	CDirectUI_Rect rc = CDirectUI_Rect(0,0,actual_rect.GetWidth(), actual_rect.GetHeight());
	if (ignore_x == false)
	{
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
	}
	if (ignore_y == false)
	{
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
	}
	
	return rc;
}

void CControl::CreateRenderBuf(ID2D1RenderTarget* pRT, D2D1_SIZE_F& data)
{
	if (this->m_pRenderBuf != NULL)
	{
		D2D1_SIZE_F sz = this->m_pRenderBuf->GetSize();
		if (sz.width != data.width || sz.height != data.height)
		{
			this->m_pRenderBuf->Release();
			this->m_pRenderBuf = NULL;
		}
	}
	if (this->m_pRenderBuf == NULL)
	{
		HRESULT hr = pRT->CreateCompatibleRenderTarget(data, &this->m_pRenderBuf);
	}
	this->m_pRenderBuf->BeginDraw();
	
	if (this->m_Background)
	{
		this->m_Background->Refresh(this->m_pRenderBuf);
		this->m_pRenderBuf->FillRectangle(D2D1::RectF(0, 0, data.width, data.height), *this->m_Background);
	}
}

void CControl::Arrange(float x, float y, float width, float height)
{
	CDirectUI_Thinkness margin = this->m_Margin;
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

	CTrace::WriteLine(L"%s: %s  Desire w:%f h:%f", this->Name.c_str(), this->m_ActualRect.ToString().c_str(), this->DesiredSize.width, this->DesiredSize.height);
}

void CControl::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	this->m_pRenderBuf->EndDraw();
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
	ID2D1Bitmap* bmp = NULL;	
	
	this->m_pRenderBuf->GetBitmap(&bmp);
	//CDirectUI_Rect rc_dst = this->m_ActualRect / this->m_DpiScale;
	CDirectUI_Rect rc_dst = this->m_ActualRect;
	CDirectUI_Rect rc_src(0, 0, this->DesiredSize.width, this->DesiredSize.height);
	//CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	rc_src = this->MappingRenderRect(this->m_ActualRect, this->DesiredSize);
	//if (this->m_ActualRect.GetWidth() < this->DesiredSize.width)
	//{
	//	rc_src.SetX(this->DesiredSize.width - this->m_ActualRect.GetWidth());
	//}
	//CTrace::WriteLine(L"%s render: %s  Desire w:%f h:%f", this->Name.c_str(), rc_dst.ToString().c_str(), rc_src.GetWidth(), rc_src.GetHeight());
	//CTrace::WriteLine(L"%s render: %s  rc_dst %s", this->Name.c_str(), rc_src.ToString().c_str(), rc_src.GetWidth(), rc_src.GetHeight());
	//float w1 = rc_dst.GetWidth();
	//float w2 = rc_src.GetWidth();
	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, rc_src);
	//::OutputDebugString(this->Name.c_str());
	//::OutputDebugStringA(" rc_dst:");
	//::OutputDebugString(rc_dst.ToString().c_str());
	//::OutputDebugStringA("\r\n");
	//::OutputDebugString(this->Name.c_str());
	//::OutputDebugStringA(" rc_src:");
	//::OutputDebugString(rc_src.ToString().c_str());
	//::OutputDebugStringA("\r\n");
	bmp->Release();
}

void CControl::SetWidth(float data) 
{ 
	this->m_Width = data; 
}

void CControl::SetHieght(float data) 
{ 
	this->m_Height = data; 
}

void CControl::SetMinWidth(float data) 
{ 
	this->m_MinWidth = data; 
}

void CControl::SetMinHieght(float data) 
{ 
	this->m_MinHeight = data; 
}

void CControl::SetMaxWidth(float data) 
{ 
	this->m_MaxWidth = data; 
}

void CControl::SetMaxHieght(float data) 
{ 
	this->m_MaxHeight = data; 
}

void CControl::SetVisibility(Visibilitys data) 
{ 
	this->m_Visibility = data; 
}

void CControl::SetVerticalAlignment(VerticalAlignments data) 
{ 
	this->m_VerticalAlignment = data; 
}

void CControl::SetHorizontalAlignment(HorizontalAlignments data)
{
	this->m_HorizontalAlignment = data;
}

void CControl::SetMargin(CDirectUI_Thinkness& data)
{ 
	this->m_Margin = data; 
}

void CControl::SetBackground(shared_ptr<Direct2D::CD2D_Brush> data)
{
	if (this->m_Background && this->m_Background != data)
	{
		this->m_Background->Release();
	}
	this->m_Background = data;
}

void CControl::SetEnabled(bool data)
{
	this->m_IsEnabled = data;
}