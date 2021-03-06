#include "pch.h"
#include "UIElement.h"
using namespace DirectUI;
using namespace Control;

ID2D1Factory* UIElement::m_pD2DFactory = NULL;
shared_ptr<DependencyProperty<int>> UIElement::HorizontalAlignmentProperty;
shared_ptr<DependencyProperty<int>> UIElement::VerticalAlignmentProperty;
shared_ptr<DependencyProperty<shared_ptr<CDirectUI_Thinkness>>> UIElement::MarginProperty;
UIElement::UIElement()
{
	if (!HorizontalAlignmentProperty)
	{
		HorizontalAlignmentProperty = ::make_shared<DependencyProperty<int>>();
		HorizontalAlignmentProperty->m_Default = (int)HorizontalAlignments::Stretch;
		HorizontalAlignmentProperty->m_Name = L"HorizontalAlignment";
	}
	this->SetValue(HorizontalAlignmentProperty, (int)HorizontalAlignments::Stretch);
	if (!VerticalAlignmentProperty)
	{
		VerticalAlignmentProperty = ::make_shared<DependencyProperty<int>>();
		VerticalAlignmentProperty->m_Default = (int)VerticalAlignments::Stretch;
		VerticalAlignmentProperty->m_Name = L"VerticalAlignment";
	}
	
	this->SetValue(VerticalAlignmentProperty, (int)VerticalAlignments::Stretch);

	if (!MarginProperty)
	{
		MarginProperty = ::make_shared<DependencyProperty<shared_ptr<CDirectUI_Thinkness>>>();
		MarginProperty->m_Default = ::make_shared<CDirectUI_Thinkness>();
		MarginProperty->m_Name = L"Margin";
	}
}

//void UIElement::BackgroundPropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs< Direct2D::CD2D_Brush>& args)
//{
//	UIElement& aa = (UIElement&)sender;
//	aa.Invalidate();
//}

bool UIElement::HitTest(int x, int y, vector<shared_ptr<UIElement>>& childs)
{
	bool result = false;

	if (this->m_Visibility == Visibilitys::Visible && this->m_ActualRect.PtInRect(x, y) == true)
	{
		childs.push_back(static_pointer_cast<UIElement>(this->shared_from_this()));
		result = true;
	}

	return result;
}

void UIElement::OnSize(float width, float height, float dpiscale)
{
	this->m_DpiScale = dpiscale;
}

void UIElement::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	if (this->m_Visibility == Visibilitys::Collapsed)
	{
		this->DesiredSize.width = this->DesiredSize.height = 0;
	}
	else
	{
		this->DesiredSize = this->GetSize(data.GetWidth(), data.GetHeight());
	}
}

void UIElement::Measure(const CDirectUI_Rect& data, ID2D1RenderTarget* pRT)
{
	CDirectUI_Rect rc = data;
	if (this->m_Width > 0)
	{
		rc.SetWidth(this->m_Width);
	}
	if (this->m_Height > 0)
	{
		rc.SetHeight(this->m_Height);
	}
	rc = rc + *this->Margin;
	float left = rc.GetLeft();
	float top = rc.GetTop();
	float w = rc.GetWidth();
	float h = rc.GetHeight();
	switch (this->HorizontalAlignment)
	{
	case HorizontalAlignments::Stretch:
	{
		//left = left + (width - w) / 2;
		if (data.GetWidth() > w)
		{
			left = left + (data.GetWidth() - w) / 2;
		}
	}
	break;
	case HorizontalAlignments::Center:
	{
		left = left + (rc.GetWidth() - w) / 2;
	}
	break;
	case HorizontalAlignments::Left:
	{
		//w = this->DesiredSize.width;
	}
	break;
	case HorizontalAlignments::Right:
	{
		left = left + (rc.GetWidth() - w);
	}
	break;
	}
	switch (this->VerticalAlignment)
	{
	case VerticalAlignments::Stretch:
	{
		if (data.GetHeight() > h)
		{
			top = top + (data.GetHeight() - h) / 2;
		}
	}
	break;
	case VerticalAlignments::Center:
	{
		top = top + (rc.GetHeight() - h) / 2;
	}
	break;
	case VerticalAlignments::Bottom:
	{
		top = top + (rc.GetHeight() - h);
	}
	break;
	}

	this->m_MeasureRect.SetLeft(left);
	this->m_MeasureRect.SetTop(top);
	this->m_MeasureRect.SetWidth(w);
	this->m_MeasureRect.SetHeight(h);
}

D2D1_SIZE_F UIElement::GetSize(float width, float height)
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

CDirectUI_Rect UIElement::MappingRenderRect1(CDirectUI_Rect& actual_rect, const CDirectUI_Size& measure_size, HorizontalAlignments horizontalalignment, VerticalAlignments verticalalignment)
{
	CDirectUI_Rect rc = actual_rect;
	switch (horizontalalignment)
	{
	case HorizontalAlignments::Center:
	{
		if (rc.GetWidth() < measure_size.GetWidth())
		{
			float offset_x = rc.GetWidth() - measure_size.GetWidth();
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
			float offset_x = rc.GetWidth() - measure_size.GetWidth();
			//CTrace::WriteLine(L"offset_x:%f", offset_x);
			rc.SetOffsetX(offset_x);
		}
	}
	break;
	}

	switch (verticalalignment)
	{
	case VerticalAlignments::Center:
	{
		if (rc.GetHeight() < measure_size.GetHeight())
		{
			float offset_y = measure_size.GetHeight() - rc.GetHeight();
			offset_y = offset_y / 2;
			rc.SetY(offset_y);
			::OutputDebugStringW(rc.ToString().c_str());
			OutputDebugStringW(L"\r\n");
		}
	}
	break;
	case VerticalAlignments::Bottom:
	{
		if (rc.GetHeight() < measure_size.GetHeight())
		{
			float offset_y = measure_size.GetHeight() - rc.GetHeight();
			rc.SetY(rc.GetTop()+ offset_y);
			//rc.SetHeight()
			CTrace::WriteLine(L"measure:%f rc:%f", measure_size.GetHeight(), rc.GetHeight());
		}
	}
	break;
	}

	return rc;
}

CDirectUI_Rect UIElement::MappingRenderRect(CDirectUI_Rect& actual_rect, const CDirectUI_Size& measure_size, bool ignore_x, bool ignore_y)
{
	CDirectUI_Rect rc = CDirectUI_Rect(0, 0, actual_rect.GetWidth(), actual_rect.GetHeight());
	if (ignore_x == false)
	{
		switch (this->HorizontalAlignment)
		{
		case HorizontalAlignments::Center:
		{
			if (rc.GetWidth() < measure_size.GetWidth())
			{
				float offset_x = measure_size.GetWidth() - rc.GetWidth();
				offset_x = offset_x / 2;
				rc.SetX(offset_x);
			}
		}
		break;
		case HorizontalAlignments::Right:
		{
			if (rc.GetWidth() < measure_size.GetWidth())
			{
				float offset_x = measure_size.GetWidth() - rc.GetWidth();
				rc.SetX(offset_x);
			}
		}
		break;
		}
	}
	if (ignore_y == false)
	{
		switch (this->VerticalAlignment)
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

CDirectUI_Rect UIElement::MeasureMapping(const CDirectUI_Rect& rc, const CDirectUI_Size& sz, HorizontalAlignments horizontalalignment, VerticalAlignments verticalalignment)
{
	CDirectUI_Rect hr;
	switch (horizontalalignment)
	{
	case HorizontalAlignments::Stretch:
	{
		if (sz.GetWidth() > rc.GetWidth())
		{
			float left = rc.GetLeft();
			hr.SetLeft(left);
			hr.SetWidth(sz.GetWidth());
		}
		else
		{
			float left = rc.GetLeft();
			left = left + (rc.GetWidth() - sz.GetWidth()) / 2;
			hr.SetLeft(left);
			hr.SetWidth(sz.GetWidth());
		}
	}
	break;
	case HorizontalAlignments::Left:
	{
		float left = rc.GetLeft();
		hr.SetLeft(left);
		hr.SetWidth(sz.GetWidth());
	}
	break;
	case HorizontalAlignments::Center:
	{
		float left = rc.GetLeft();
		left = left + (rc.GetWidth() - sz.GetWidth()) / 2;
		hr.SetLeft(left);
		hr.SetWidth(sz.GetWidth());
	}
	break;
	case HorizontalAlignments::Right:
	{
		float left = rc.GetLeft();
		left = left + rc.GetWidth() - sz.GetWidth();
		hr.SetLeft(left);
		hr.SetWidth(sz.GetWidth());
	}
	break;
	}

	switch (verticalalignment)
	{
	case VerticalAlignments::Stretch:
	{
		if (sz.GetHeight() > rc.GetHeight())
		{
			float top = rc.GetTop();
			hr.SetTop(top);
			hr.SetHeight(sz.GetHeight());
		}
		else
		{
			float top = rc.GetTop();
			top = top + (rc.GetHeight() - sz.GetHeight()) / 2;
			hr.SetTop(top);
			hr.SetHeight(sz.GetHeight());
		}
	}
	break;
	case VerticalAlignments::Top:
	{
		float top = rc.GetTop();
		hr.SetTop(top);
		hr.SetHeight(sz.GetHeight());
	}
	break;
	case VerticalAlignments::Center:
	{
		float top = rc.GetTop();
		top = top + (rc.GetHeight() - sz.GetHeight()) / 2;
		hr.SetTop(top);
		hr.SetHeight(sz.GetHeight());
	}
	break;
	case VerticalAlignments::Bottom:
	{
		float top = rc.GetTop();
		top = top + rc.GetHeight() - sz.GetHeight();
		hr.SetTop(top);
		hr.SetHeight(sz.GetHeight());
	}
	break;
	}
	return hr;
}

void UIElement::CreateRenderBuf(ID2D1RenderTarget* pRT, const CDirectUI_Size& data, shared_ptr<Direct2D::CD2D_Brush> background)
{
	//if (this->m_pRenderBuf != NULL)
	//{
	//	D2D1_SIZE_F sz = this->m_pRenderBuf->GetSize();
	//	if (data != sz)
	//	{
	//		this->m_pRenderBuf->Release();
	//		this->m_pRenderBuf = NULL;
	//	}
	//}
	//if (this->m_pRenderBuf == NULL)
	//{
	//	HRESULT hr = pRT->CreateCompatibleRenderTarget(data, &this->m_pRenderBuf);
	//}
	//this->m_pRenderBuf->BeginDraw();


	//if (background)
	//{
	//	background->Refresh(this->m_pRenderBuf);
	//	this->m_pRenderBuf->FillRectangle(data, *background);
	//}
	
}

void UIElement::Arrange(const CDirectUI_Rect& data)
{
	if (data == 0)
	{
		this->m_ActualRect = data;
		return;
	}
	this->DesiredSize = this->m_MeasureRect;
	CDirectUI_Rect rc = data + *this->Margin;
	D2D1_SIZE_F sz = this->GetSize(rc.GetWidth(), rc.GetHeight());
	float left = rc.GetLeft();
	float top = rc.GetTop();
	float right = left + sz.width;
	if (rc.GetWidth() < sz.width)
	{
		right = left + rc.GetWidth();
	}
	float bottom = top + sz.height;
	if (rc.GetHeight() < sz.height)
	{
		bottom = top + rc.GetHeight();
	}
	float w = right - left;
	//if (this->m_HorizontalAlignment != HorizontalAlignments::Stretch)
	{
		if (w > this->DesiredSize.width)
		{
			w = this->DesiredSize.width;
		}
	}
	if (data.GetWidth() == 0)
	{
		w = this->DesiredSize.width;
	}
	float h = bottom - top;
	//if (this->m_VerticalAlignment != VerticalAlignments::Stretch)
	{
		if (h > this->DesiredSize.height)
		{
			h = this->DesiredSize.height;
		}
	}
	//if (data.GetHeight() == 0)
	//{
	//	h = this->DesiredSize.height;
	//}
	switch (this->HorizontalAlignment)
	{
	case HorizontalAlignments::Stretch:
	{
		//left = left + (width - w) / 2;
		if (rc.GetWidth() > this->DesiredSize.width)
		{
			left = left + (rc.GetWidth() - w) / 2;
		}
	}
	break;
	case HorizontalAlignments::Center:
	{
		//w = this->DesiredSize.width;
		left = left + (rc.GetWidth() - w) / 2;
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
		left = left + (rc.GetWidth() - w);
	}
	break;
	}
	switch (this->VerticalAlignment)
	{
	case VerticalAlignments::Stretch:
	{
		if (rc.GetHeight() > this->DesiredSize.height)
		{
			top = top + (rc.GetHeight() - h) / 2;
		}
	}
	break;
	case VerticalAlignments::Center:
	{
		top = top + (rc.GetHeight() - h) / 2;
	}
	break;
	case VerticalAlignments::Bottom:
	{
		top = top + (rc.GetHeight() - h);
	}
	break;
	}

	this->m_ActualRect.SetLeft(left);
	this->m_ActualRect.SetTop(top);
	this->m_ActualRect.SetWidth(w);
	this->m_ActualRect.SetHeight(h);

	//CTrace::WriteLine(L"%s: %s  Desire w:%f h:%f", this->Name.c_str(), this->m_ActualRect.ToString().c_str(), this->DesiredSize.width, this->DesiredSize.height);
}

void UIElement::OnRender(ID2D1RenderTarget* pRT)
{
	this->m_pRenderBuf->EndDraw();
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
	ID2D1Bitmap* bmp = NULL;

	this->m_pRenderBuf->GetBitmap(&bmp);

	CDirectUI_Rect rc_dst = this->m_ActualRect;
	CDirectUI_Rect rc_src = this->DesiredSize;

	rc_src = this->MappingRenderRect(this->m_ActualRect, this->DesiredSize);

	pRT->DrawBitmap(bmp, rc_dst, this->m_Opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, rc_src);

	bmp->Release();
}

void UIElement::SetWidth(float data)
{
	this->m_Width = data;
}

void UIElement::SetHieght(float data)
{
	this->m_Height = data;
}

void UIElement::SetMinWidth(float data)
{
	this->m_MinWidth = data;
}

void UIElement::SetMinHieght(float data)
{
	this->m_MinHeight = data;
}

void UIElement::SetMaxWidth(float data)
{
	this->m_MaxWidth = data;
}

void UIElement::SetMaxHieght(float data)
{
	this->m_MaxHeight = data;
}

void UIElement::SetVisibility(Visibilitys data)
{
	this->m_Visibility = data;
}

void UIElement::SetVerticalAlignment(VerticalAlignments data)
{
	this->SetValue(VerticalAlignmentProperty, (int)data);
	//this->m_VerticalAlignment = data;
}

VerticalAlignments UIElement::GetVerticalAlignment()
{
	return (VerticalAlignments)this->GetValue(VerticalAlignmentProperty);
}

void UIElement::SetHorizontalAlignment(HorizontalAlignments data)
{
	this->SetValue(HorizontalAlignmentProperty, (int)data);
	//this->m_HorizontalAlignment = data;
}

HorizontalAlignments UIElement::GetHorizontalAlignment()
{
	return (HorizontalAlignments)this->GetValue(HorizontalAlignmentProperty);
}

void UIElement::SetEnabled(bool data)
{
	this->m_IsEnabled = data;
}

void UIElement::SetCaptureMouse(bool data)
{
	this->m_IsCaptureMouse = data;
}

void UIElement::Invalidate()
{
	auto wp = this->m_Root.lock();
	if (wp)
	{
		wp->Invalidate();
	}
}

void UIElement::InvalidateArrange()
{
	auto wp = this->m_Root.lock();
	if (wp)
	{
		wp->InvalidateArrange();
	}
}

void UIElement::InvalidateMeasurce()
{
	auto wp = this->m_Root.lock();
	if (wp)
	{
		wp->InvalidateMeasurce();
	}
}

void UIElement::SetMargin(shared_ptr<CDirectUI_Thinkness> data)
{
	this->SetValue(MarginProperty, data);
}

shared_ptr<CDirectUI_Thinkness> UIElement::GetMargin()
{
	return this->GetValue<shared_ptr<CDirectUI_Thinkness>>(MarginProperty);

	return nullptr;
}