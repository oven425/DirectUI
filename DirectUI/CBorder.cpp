#include "pch.h"
#include "CBorder.h"
using namespace DirectUI;
using namespace Control;

void CBorder::OnRender(ID2D1RenderTarget* pRT)
{
	if (this->BorderThickness > 0)
	{
		//::CControl::OnRender(pRT);

		if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
		{
			return;
		}
		
		CDirectUI_Thinkness thinkness(this->BorderThickness / 2);
		//CDirectUI_Rect rc = (this->m_ActualRect + thinkness) / this->m_DpiScale;
		CDirectUI_Rect rc = (this->m_ActualRect) / this->m_DpiScale;
		ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
		HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);
		
		pCompatibleRenderTarget->BeginDraw();
		if (BorderBrush)
		{
			this->BorderBrush->Release();
			this->BorderBrush->Refresh(pCompatibleRenderTarget);
			ID2D1Brush* m_pBlackBrush = this->BorderBrush->operator ID2D1Brush*();
			D2D1_RECT_F rc1 = { 0 };
			rc1.right = this->DesiredSize.width;
			rc1.bottom = this->DesiredSize.height;
			pCompatibleRenderTarget->DrawRectangle(CDirectUI_Rect(0,0,this->DesiredSize.width, this->DesiredSize.height) + thinkness, m_pBlackBrush, this->BorderThickness / this->m_DpiScale);
		}
		pCompatibleRenderTarget->EndDraw();
		ID2D1Bitmap* bmp = NULL;
		pCompatibleRenderTarget->GetBitmap(&bmp);
		pRT->DrawBitmap(bmp, rc);
		bmp->Release();
		pCompatibleRenderTarget->Release();

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
