#include "pch.h"
#include "CThumb.h"
using namespace DirectUI;
using namespace Control;

void CThumb::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);

	::CControl::OnRender(pRT, calculate_dpi);
}

void CThumb::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	this->DesiredSize = data + this->m_Margin;
	if (this->m_Width > 0)
	{
		this->DesiredSize.width = this->m_Width;
	}
	if (this->m_Height > 0)
	{
		this->DesiredSize.height = this->m_Height;
	}

}

void CThumb::Arrange(float x, float y, float width, float height)
{
	::CControl::Arrange(x, y, width, height);
}

void CThumb::OnMouseMove(const MouseMoveArgs& args)
{
	::CControl::OnMouseMove(args);
	if (this->DragDeltaHandler)
	{

	}
}

void CThumb::OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args)
{
	::CControl::OnMouseLeftButtonDown(args);
	if (this->DragStartedHandler)
	{

	}
}

void CThumb::OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args)
{
	::CControl::OnMouseLeftButtonUp(args);
	if (this->DragCompletedHandler)
	{

	}
}