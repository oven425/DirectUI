#include "pch.h"
#include "CBorder.h"
using namespace DirectUI;
using namespace Control;

void CBorder::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	if (this->m_BorderThickness > 0)
	{
		//::CControl::OnRender(pRT);

		if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
		{
			return;
		}
		
		//CDirectUI_Rect rc = (this->m_ActualRect + thinkness) / this->m_DpiScale;
		CDirectUI_Rect rc = (this->m_ActualRect) / this->m_DpiScale;
		ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
		






		
		//pCompatibleRenderTarget->BeginDraw();
		if (BorderBrush)
		{
			//this->BorderBrush->Release();
			this->BorderBrush->Refresh(pCompatibleRenderTarget);
			ID2D1Brush* m_pBlackBrush = this->BorderBrush->operator ID2D1Brush*();
			//D2D1_RECT_F rc1 = { 0 };
			//rc1.right = this->DesiredSize.width;
			//rc1.bottom = this->DesiredSize.height;
			//pCompatibleRenderTarget->DrawRectangle(CDirectUI_Rect(0,0,this->DesiredSize.width, this->DesiredSize.height) + thinkness, m_pBlackBrush, this->BorderThickness / this->m_DpiScale);

			HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);

			hr = m_pD2DFactory->CreatePathGeometry(&this->m_pBorder);
			if (SUCCEEDED(hr))
			{

				ID2D1GeometrySink *pSink = NULL;

				hr = m_pBorder->Open(&pSink);
				if (SUCCEEDED(hr))
				{
					pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

					pSink->BeginFigure(
						D2D1::Point2F(0, 0),
						D2D1_FIGURE_BEGIN_FILLED
					);
					pSink->AddLine(D2D1::Point2F(this->DesiredSize.width, 10));

					pSink->AddArc(
						D2D1::ArcSegment(
							D2D1::Point2F(100, 20), // end point
							D2D1::SizeF(10, 10),
							0.0f, // rotation angle
							D2D1_SWEEP_DIRECTION_CLOCKWISE,
							D2D1_ARC_SIZE_SMALL
						));
					pSink->AddLine(D2D1::Point2F(100, 90));
					pSink->AddArc(
						D2D1::ArcSegment(
							D2D1::Point2F(90, 100), // end point
							D2D1::SizeF(10, 10),
							0.0f, // rotation angle
							D2D1_SWEEP_DIRECTION_CLOCKWISE,
							D2D1_ARC_SIZE_SMALL
						));
					pSink->AddLine(D2D1::Point2F(10, 100));


					pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
				}

				hr = pSink->Close();
			}
			//this->Background->Refresh(pRT);
			//pRT->DrawGeometry(m_pSunGeometry, *this->Background, 1.f);
			


		}
		pCompatibleRenderTarget->EndDraw();
		ID2D1Bitmap* bmp = NULL;
		pCompatibleRenderTarget->GetBitmap(&bmp);

		//pRT->DrawBitmap(bmp, rc);
		CDirectUI_Rect rc_dst = rc;
		CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight()) ;
		pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);
		bmp->Release();
		pCompatibleRenderTarget->Release();

		if (this->m_Child != nullptr)
		{
			this->m_Child->OnRender(pRT, calculate_dpi);
		}
	}
	else
	{
		::CContentControl::OnRender(pRT, calculate_dpi);
	}
}

void CBorder::Arrange(float x, float y, float width, float height)
{
	::CContentControl::Arrange(x, y, width, height);
}

void CBorder::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	::CContentControl::Measure(width, height, pRT);
}

void CBorder::SetCornerRadius(CDirectUI_Thinkness& data)
{
	if (this->m_CornerRadius != data)
	{
		this->m_CornerRadius = data;
		this->Release();
	}
	
}

void CBorder::SetBorderThickness(CDirectUI_Thinkness& data)
{
	if (this->m_BorderThickness != data)
	{
		this->m_BorderThickness = data;
		this->Release();
	}
}

void CBorder::Release()
{
	if (this->m_pBorder != NULL)
	{
		this->m_pBorder->Release();
		this->m_pBorder = NULL;
	}
}
