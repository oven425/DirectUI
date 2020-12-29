#include "pch.h"
#include "CBorder.h"
using namespace DirectUI;
using namespace Control;

void CBorder::OnRender(ID2D1HwndRenderTarget* pRT)
{
	if (this->BorderThickness > 0)
	{
		::CControl::OnRender(pRT);


		//D2D1_RECT_F size = { 0 };
		CDirectUI_Thinkness thinkness(this->BorderThickness/2);
		CDirectUI_Rect rc = (this->m_ActualRect + thinkness) / this->m_DpiScale;

		//size.bottom = (this->m_ActualRect.GetBottom()-this->BorderThickness/2)/this->m_DpiScale;
		//size.left = (this->m_ActualRect.GetX() + this->BorderThickness / 2) / this->m_DpiScale;
		//size.right = (this->m_ActualRect.GetWidth()-this->BorderThickness / 2) / this->m_DpiScale;
		//size.top = (this->m_ActualRect.GetY()+this->BorderThickness / 2) / this->m_DpiScale;
		//char msg[255] = { 0 };
		//::sprintf_s(msg, "a left:%f top:%f right:%f bottom:%f\r\n", size.left, size.top, size.right, size.bottom);
		//::OutputDebugStringA(msg);
		//::sprintf_s(msg, "b left:%f top:%f right:%f bottom:%f\r\n", rc.GetLeft(), rc.GetTop(), rc.GetRight(), rc.GetBottom());
		//::OutputDebugStringA(msg);
		if (BorderBrush.use_count() > 0)
		{
			this->BorderBrush->Refresh(pRT);
			ID2D1Brush* m_pBlackBrush = this->BorderBrush->operator ID2D1Brush*();
			pRT->DrawRectangle(rc, m_pBlackBrush, this->BorderThickness / this->m_DpiScale);
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
