#include "pch.h"
#include "CControl.h"
using namespace DirectUI;
using namespace Control;

void CControl::OnRender(ID2D1HwndRenderTarget* pRT)
{
	D2D1_RECT_F size = { 0 };
	size.bottom = this->m_Height-10;
	size.left = 0;
	size.right = this->m_Width-10;
	size.top = 0;
	this->Background->Refresh(pRT);
	ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();

	pRT->FillRectangle(size, m_pBlackBrush);
	
}