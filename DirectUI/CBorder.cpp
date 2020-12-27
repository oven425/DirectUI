#include "pch.h"
#include "CBorder.h"
using namespace DirectUI;
using namespace Control;

void CBorder::Measure(int width, int height)
{
	this->DesiredSize.cx = width;
	this->DesiredSize.cy = height;
}

void CBorder::OnRender(ID2D1HwndRenderTarget* pRT)
{
	if (this->BorderThickness > 0)
	{
		::CControl::OnRender(pRT);


		D2D1_RECT_F size = { 0 };
		size.bottom = (this->m_ActualHeight-this->BorderThickness/2)/this->m_DpiScale;
		size.left = this->BorderThickness / 2 /this->m_DpiScale;
		size.right = (this->m_ActualWidth-this->BorderThickness / 2) / this->m_DpiScale;
		size.top = this->BorderThickness / 2 / this->m_DpiScale;
		if (BorderBrush.use_count() > 0)
		{
			this->BorderBrush->Refresh(pRT);
			ID2D1Brush* m_pBlackBrush = this->BorderBrush->operator ID2D1Brush*();
			pRT->DrawRectangle(size, m_pBlackBrush, this->BorderThickness / this->m_DpiScale);
		}
		

		if (this->m_Child != nullptr)
		{
			this->m_Child->OnRender(pRT);
		}

	}
	else
	{
		::CContentControl::OnRender(pRT);
	}
	
	
	
	
}
