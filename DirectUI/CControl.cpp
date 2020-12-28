#include "pch.h"
#include "CControl.h"
using namespace DirectUI;
using namespace Control;

void CControl::OnSize(double width, double height, double dpiscale)
{
	//this->m_Width = width;
	//this->m_Height = height;
	this->m_DpiScale = dpiscale;
	
	//this->Measure(width, height);
}

void CControl::OnRender(ID2D1HwndRenderTarget* pRT)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
	CDirectUI_Rect rc = (this->m_ActualRect) / this->m_DpiScale;
	if (this->Background.use_count() > 0)
	{
		this->Background->Refresh(pRT);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
		pRT->FillRectangle(rc, m_pBlackBrush);
	}
	
	
}
