#include "pch.h"
#include "Rectangle.h"
#include "CDirectUI_RoundedRect.h"
using namespace DirectUI;
using namespace Control;
using namespace Shapes;



shared_ptr<DependencyProperty<float>> Rectangle::RadiusXProperty;
shared_ptr<DependencyProperty<float>> Rectangle::RadiusYProperty;

Rectangle::Rectangle()
{
	if (!RadiusXProperty)
	{
		RadiusXProperty = ::make_shared<DependencyProperty<float>>();
	}
	if (!RadiusYProperty)
	{
		RadiusYProperty = ::make_shared<DependencyProperty<float>>();
	}
}

void Rectangle::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Size sz = data + *this->Margin;
	if (this->m_Width > 0)
	{
		switch (this->Stretch)
		{
		case Stretchs::Uniform:
		case Stretchs::UniformToFill:
		case Stretchs::Fill:
		{
			sz.SetWidth(this->m_Width);
		}
		break;
		}
	}

	if (this->m_Height > 0)
	{
		switch (this->Stretch)
		{
		case Stretchs::Uniform:
		case Stretchs::UniformToFill:
		case Stretchs::Fill:
		{
			sz.SetHeight(this->m_Height);
		}
		break;
		}
	}

	this->DesiredSize = sz;


	//switch (this->Stretch)
	//{
	//
	//case Stretchs::Fill:
	//{
	//	this->DesiredSize = sz;
	//}
	//break;
	//case Stretchs::Uniform:
	//{
	//	this->DesiredSize = sz;
	//	this->DesiredSize.width = this->DesiredSize.height =min(this->DesiredSize.width, this->DesiredSize.height);
	//}
	//break;
	//case Stretchs::UniformToFill:
	//{
	//	this->DesiredSize = sz;
	//	this->DesiredSize.width = this->DesiredSize.height = max(this->DesiredSize.width, this->DesiredSize.height);
	//}
	//break;
	//case Stretchs::None:
	//default:
	//{

	//}
	//break;
	//}
}

void Rectangle::Arrange(const CDirectUI_Rect& data)
{
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
	float h = bottom - top;
	//if (this->m_VerticalAlignment != VerticalAlignments::Stretch)
	{
		if (h > this->DesiredSize.height)
		{
			h = this->DesiredSize.height;
		}
	}
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



	//this->m_ActualRect = this->DesiredSize;
}

void Rectangle::OnRender(ID2D1RenderTarget* pRT)
{
	//this->CreateRenderBuf(pRT, this->DesiredSize, false);
	//CDirectUI_Rect render_rc = this->DesiredSize;
	//switch (this->Stretch)
	//{
	//case Stretchs::Uniform:
	//{
	//	render_rc = CDirectUI_Rect(min(this->DesiredSize.width, this->DesiredSize.height));
	//}
	//break;
	//case Stretchs::UniformToFill:
	//{
	//	render_rc = CDirectUI_Rect(max(this->DesiredSize.width, this->DesiredSize.height));
	//}
	//break;
	//}
	//if (this->Fill)
	//{
	//	this->Fill->Refresh(pRT);
	//	float radius_x = this->RadiusX;
	//	float radius_y = this->RadiusY;
	//	if (radius_x > 0 && radius_y > 0)
	//	{
	//		CDirectUI_RoundedRect rounded(render_rc, radius_x, radius_y);
	//		this->m_pRenderBuf->FillRoundedRectangle(rounded, *this->Fill);
	//	}
	//	else
	//	{
	//		this->m_pRenderBuf->FillRectangle(render_rc, *this->Fill);
	//	}
	//	
	//}
	//if (this->StrokeThickness > 0 && this->Stroke)
	//{
	//	this->Stroke->Refresh(pRT);
	//	auto br = *this->Stroke;
	//	this->m_pRenderBuf->DrawEllipse(CDirectUI_Rect(this->DesiredSize) + this->StrokeThickness / 2, *this->Stroke, this->StrokeThickness);
	//}

	//Control::UIElement::OnRender(pRT);

	pRT->PushAxisAlignedClip(this->m_ActualRect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	CDirectUI_Rect render_rc = this->m_ActualRect;
	switch (this->Stretch)
	{
	case Stretchs::Uniform:
	{
		//render_rc = CDirectUI_Rect(min(this->DesiredSize.width, this->DesiredSize.height));
		float ff = min(this->DesiredSize.width, this->DesiredSize.height);
		render_rc.SetWidth(ff);
		render_rc.SetHeight(ff);
	}
	break;
	case Stretchs::UniformToFill:
	{
		//render_rc = CDirectUI_Rect(max(this->DesiredSize.width, this->DesiredSize.height));
		float ff = max(this->DesiredSize.width, this->DesiredSize.height);
		render_rc.SetWidth(ff);
		render_rc.SetHeight(ff);
	}
	break;
	}
	if (this->Fill)
	{
		this->Fill->Refresh(pRT);
		float radius_x = this->RadiusX;
		float radius_y = this->RadiusY;
		if (radius_x > 0 && radius_y > 0)
		{
			CDirectUI_RoundedRect rounded(render_rc, radius_x, radius_y);
			pRT->FillRoundedRectangle(rounded, *this->Fill);
		}
		else
		{
			pRT->FillRectangle(render_rc, *this->Fill);
		}
		
	}
	if (this->StrokeThickness > 0 && this->Stroke)
	{
		this->Stroke->Refresh(pRT);
		pRT->DrawEllipse(CDirectUI_Rect(this->DesiredSize) + this->StrokeThickness / 2, *this->Stroke, this->StrokeThickness);
	}

	pRT->PopAxisAlignedClip();

}

void Rectangle::SetRadiusX(float data)
{
	this->SetValue(RadiusXProperty, data);
}

float Rectangle::GetRadiusX()
{
	return this->GetValue<float>(RadiusXProperty);
}

void Rectangle::SetRadiusY(float data)
{
	this->SetValue(RadiusYProperty, data);
}

float Rectangle::GetRadiusY()
{
	return this->GetValue<float>(RadiusYProperty);
}