#include "pch.h"
#include "CControl.h"
using namespace DirectUI;
using namespace Control;

void CControl::OnSize(double width, double height, double dpiscale)
{
	this->m_Width = width;
	this->m_Height = height;
	this->m_DpiScale = dpiscale;
}

void CControl::OnRender(ID2D1HwndRenderTarget* pRT)
{
	D2D1_RECT_F size = { 0 };
	size.bottom = (this->m_Height)/this->m_DpiScale;
	size.left = 0;
	size.right = (this->m_Width)/this->m_DpiScale;
	size.top = 0;
	if (this->Background.use_count() > 0)
	{
		this->Background->Refresh(pRT);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
		pRT->FillRectangle(size, m_pBlackBrush);
	}
	
	
}