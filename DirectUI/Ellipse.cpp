#include "pch.h"
#include "Ellipse.h"
using namespace DirectUI;
using namespace Shapes;

void Ellipse::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	CDirectUI_Size sz = data + this->m_Margin;
	if (this->m_Width > 0)
	{
		sz.SetWidth(this->m_Width);
	}
	if (this->m_Height > 0)
	{
		sz.SetHeight(this->m_Height);
	}
	this->DesiredSize = sz;
	switch (this->Stretch)
	{
	
	case Stretchs::Fill:
	{
		
	}
	break;
	case Stretchs::Uniform:
	{
		this->DesiredSize.width = this->DesiredSize.height =min(this->DesiredSize.width, this->DesiredSize.height);
	}
	break;
	case Stretchs::UniformToFill:
	{
		this->DesiredSize.width = this->DesiredSize.height = max(this->DesiredSize.width, this->DesiredSize.height);
	}
	break;
	case Stretchs::None:
	default:
	{

	}
	break;
	}
	//::Control::UIElement::Measure(data, pRT);
}

void Ellipse::Arrange(const CDirectUI_Rect& data)
{
	CDirectUI_Rect rc = data + this->m_Margin;
	

	
	this->m_ActualRect = rc;
}

void Ellipse::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize, false);
	if (this->Fill)
	{
		this->Fill->Refresh(pRT);
		this->m_pRenderBuf->FillEllipse(this->m_ActualRect, *this->Fill);
	}
	if (this->StrokeThickness>0 && this->Stroke)
	{
		this->Stroke->Refresh(pRT);
		auto br = *this->Stroke;
		this->m_pRenderBuf->DrawEllipse(this->m_ActualRect+this->StrokeThickness/2, *this->Stroke, this->StrokeThickness);
	}

	Control::UIElement::OnRender(pRT);
	
}

