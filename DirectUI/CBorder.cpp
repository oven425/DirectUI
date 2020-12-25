#include "pch.h"
#include "CBorder.h"
using namespace DirectUI;
using namespace Control;

CBorder::CBorder()
{

}

CBorder::CBorder(const CBorder& data)
{

}

CBorder::CBorder(const CBorder&& data)
{

}

void CBorder::Measure(int width, int height)
{
	this->DesiredSize.cx = width;
	this->DesiredSize.cy = height;
}

void CBorder::OnRender(ID2D1HwndRenderTarget* pRT)
{
	if (this->BorderThickness > 0)
	{
		//::CContentControl::OnRender(pRT);

		//D2D1_RECT_F size = { 0 };
		//size.bottom = this->m_Height- 150;
		//size.left = this->BorderThickness/2;
		//size.right = this->m_Width- this->BorderThickness / 2;
		//size.top = this->BorderThickness/2;
		//this->BorderBrush->Refresh(pRT);
		//ID2D1Brush* m_pBlackBrush = this->BorderBrush->operator ID2D1Brush*();

		//pRT->DrawRectangle(size, m_pBlackBrush, -this->BorderThickness);

	}
	else
	{
		::CContentControl::OnRender(pRT);
	}
	
	
	
	if (this->m_Child != nullptr)
	{

	}
}
