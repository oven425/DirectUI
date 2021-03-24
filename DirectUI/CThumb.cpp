#include "pch.h"
#include "CThumb.h"
using namespace DirectUI;
using namespace Control;

void CThumb::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);

	::CControl::OnRender(pRT);
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

void CThumb::Arrange(const CDirectUI_Rect& data)
{
	::CControl::Arrange(data);
	//this->m_LastPoint.SetXY(this->m_ActualRect.GetX(), this->m_ActualRect.GetY());
}

void CThumb::OnMouseMove(const MouseMoveArgs& args)
{
	::CControl::OnMouseMove(args);
	if (this->DragDeltaHandler && this->m_IsCaptureMouse==true)
	{
		//CDirectUI_Point pt = CDirectUI_Point(args.X, args.Y) - this->m_LastPoint;
		//DragDeltaEventArgs event_args;
		//event_args.HorizontalChange = pt.GetX();
		//event_args.VerticalChange = pt.GetY();
		//this->DragDeltaHandler(static_pointer_cast<CControl>(this->shared_from_this()), event_args);

		DragDeltaEventArgs event_args;
		//event_args.HorizontalChange = args.X - this->m_ActualRect.GetX() - this->m_LastPoint.GetX();
		//event_args.VerticalChange = args.Y - this->m_ActualRect.GetY() - this->m_LastPoint.GetY();

		float x_dpi = args.X;
		x_dpi = x_dpi / this->m_DpiScale;
		float y_dpi = args.Y;
		y_dpi = y_dpi / this->m_DpiScale;
		event_args.HorizontalChange = x_dpi - this->m_ActualRect.GetX();
		event_args.VerticalChange = y_dpi - this->m_ActualRect.GetY();


		char msg[512] = { 0 };
		::sprintf_s(msg, "args.X:%d, args.Y:%d X:%f Y:%f hor:%f ver:%f\r\n", args.X, args.Y, this->m_ActualRect.GetX(), this->m_ActualRect.GetY(), event_args.HorizontalChange, event_args.VerticalChange);
		::OutputDebugStringA(msg);
		this->DragDeltaHandler(static_pointer_cast<CControl>(this->shared_from_this()), event_args);
	}
}

void CThumb::OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args)
{
	::CControl::OnMouseLeftButtonDown(args);
	this->m_IsCaptureMouse = true;
	if (this->DragStartedHandler)
	{
		DragStartedEventArgs event_args;
		event_args.HorizontalOffset = args.X - this->m_ActualRect.GetX();
		event_args.VerticalOffset = args.Y - this->m_ActualRect.GetY();
		this->DragStartedHandler(static_pointer_cast<CControl>(this->shared_from_this()), event_args);
		this->m_LastPoint.SetXY(args.X, args.Y);
	}
}

void CThumb::OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args)
{
	::CControl::OnMouseLeftButtonUp(args);
	this->m_IsCaptureMouse = false;
	if (this->DragCompletedHandler)
	{
		CDirectUI_Point pt = this->m_LastPoint - CDirectUI_Point(args.X, args.Y);
		DragCompletedEventArgs event_args;
		event_args.HorizontalChange = pt.GetX();
		event_args.VerticalChange = pt.GetY();
		this->DragCompletedHandler(static_pointer_cast<CControl>(this->shared_from_this()), event_args);
	}
}