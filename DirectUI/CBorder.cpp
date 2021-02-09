#include "pch.h"
#include "CBorder.h"
using namespace DirectUI;
using namespace Control;


ID2D1PathGeometry* CBorder::BuildPath(CDirectUI_Rect rc, CDirectUI_CornerRadius corner_radius, CDirectUI_Thinkness thinkness)
{
	ID2D1PathGeometry* path = NULL;
	HRESULT hr = m_pD2DFactory->CreatePathGeometry(&path);
	if (SUCCEEDED(hr))
	{
		ID2D1GeometrySink *pSink = NULL;
		hr = path->Open(&pSink);
		if (SUCCEEDED(hr))
		{
			pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
			if (corner_radius.GetTopLeft() > 0)
			{
				pSink->BeginFigure(
					D2D1::Point2F(rc.GetLeft() + corner_radius.GetTopLeft() + thinkness.GetLeft(), rc.GetTop()),
					D2D1_FIGURE_BEGIN_FILLED
				);
			}
			else
			{
				pSink->BeginFigure(D2D1::Point2F(rc.GetLeft(), rc.GetTop()), D2D1_FIGURE_BEGIN_FILLED);
			}
			if (corner_radius.GetTopRight() > 0)
			{
				pSink->AddLine(D2D1::Point2F(rc.GetRight() - corner_radius.GetTopRight() - thinkness.GetRight(), rc.GetTop()));
			}
			else
			{
				pSink->AddLine(D2D1::Point2F(rc.GetRight(), rc.GetTop()));
			}

			if (corner_radius.GetTopRight() > 0)
			{
				pSink->AddArc(
					D2D1::ArcSegment(
						D2D1::Point2F(rc.GetRight(), rc.GetTop() + corner_radius.GetTopRight() + thinkness.GetRight()), // end point
						D2D1::SizeF(corner_radius.GetTopRight() + thinkness.GetRight(), corner_radius.GetTopRight() + thinkness.GetRight()),
						0.0f, // rotation angle
						D2D1_SWEEP_DIRECTION_CLOCKWISE,
						D2D1_ARC_SIZE_SMALL
					));
			}
			if (corner_radius.GetBottomRight() > 0)
			{
				pSink->AddLine(D2D1::Point2F(rc.GetRight(), rc.GetBottom() - corner_radius.GetBottomRight() - thinkness.GetBottom()));
			}
			else
			{
				pSink->AddLine(D2D1::Point2F(rc.GetRight(), rc.GetBottom()));
			}

			if (corner_radius.GetBottomRight() > 0)
			{
				pSink->AddArc(
					D2D1::ArcSegment(
						D2D1::Point2F(rc.GetRight() - corner_radius.GetBottomRight() - thinkness.GetRight(), rc.GetBottom()), // end point
						D2D1::SizeF(corner_radius.GetBottomRight() + thinkness.GetRight(), corner_radius.GetBottomRight() + thinkness.GetBottom()),
						0.0f, // rotation angle
						D2D1_SWEEP_DIRECTION_CLOCKWISE,
						D2D1_ARC_SIZE_SMALL
					));
			}
			if (corner_radius.GetBottomLeft() > 0)
			{
				pSink->AddLine(D2D1::Point2F(rc.GetLeft() + corner_radius.GetBottomLeft() + thinkness.GetLeft(), rc.GetBottom()));
			}
			else
			{
				pSink->AddLine(D2D1::Point2F(rc.GetLeft(), rc.GetBottom()));
			}

			if (corner_radius.GetBottomLeft() > 0)
			{
				pSink->AddArc(
					D2D1::ArcSegment(
						D2D1::Point2F(rc.GetLeft(), rc.GetBottom() - corner_radius.GetBottomLeft() - +thinkness.GetLeft()), // end point
						D2D1::SizeF(corner_radius.GetBottomLeft() + thinkness.GetLeft(), corner_radius.GetBottomLeft() + thinkness.GetBottom()),
						0.0f, // rotation angle
						D2D1_SWEEP_DIRECTION_CLOCKWISE,
						D2D1_ARC_SIZE_SMALL
					));
			}
			if (corner_radius.GetTopLeft() > 0)
			{
				pSink->AddLine(D2D1::Point2F(rc.GetLeft(), rc.GetTop() + corner_radius.GetTopLeft() + thinkness.GetTop()));
			}
			else
			{
				pSink->AddLine(D2D1::Point2F(rc.GetLeft(), rc.GetTop()));
			}


			if (corner_radius.GetTopLeft() > 0)
			{
				pSink->AddArc(
					D2D1::ArcSegment(
						D2D1::Point2F(rc.GetLeft() + corner_radius.GetTopLeft() + thinkness.GetLeft(), rc.GetTop()), // end point
						D2D1::SizeF(corner_radius.GetTopLeft() + thinkness.GetLeft(), corner_radius.GetTopLeft() + thinkness.GetTop()),
						0.0f, // rotation angle
						D2D1_SWEEP_DIRECTION_CLOCKWISE,
						D2D1_ARC_SIZE_SMALL
					));
			}

			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		}

		hr = pSink->Close();
	}
	return path;
}


void CBorder::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}

	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);







	pCompatibleRenderTarget->BeginDraw();
	CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
	rc = rc / this->m_DpiScale;
	//CDirectUI_CornerRadius m_CornerRadius(100, 100, 100, 20);
	m_CornerRadius = m_CornerRadius / this->m_DpiScale;

	//CDirectUI_Thinkness m_BorderThickness(10);
	m_BorderThickness = m_BorderThickness / this->m_DpiScale;
	//HRESULT hr = S_OK;
	ID2D1GeometrySink *pGeometrySink = NULL;


	ID2D1PathGeometry* m_pPathGeometryUnion = NULL;
	CDirectUI_Thinkness thinkness = m_BorderThickness / 2;
	ID2D1PathGeometry* m_pBorder = this->BuildPath(rc, m_CornerRadius - thinkness, thinkness);

	CDirectUI_Thinkness thinkness1 = m_BorderThickness / 2;
	ID2D1PathGeometry* m_pCircleGeometry2 = this->BuildPath(rc + m_BorderThickness, m_CornerRadius - thinkness, -thinkness1);



	if (SUCCEEDED(hr))
	{
		//
		// Use D2D1_COMBINE_MODE_UNION to combine the geometries.
		//
		hr = m_pD2DFactory->CreatePathGeometry(&m_pPathGeometryUnion);

		if (SUCCEEDED(hr))
		{
			hr = m_pPathGeometryUnion->Open(&pGeometrySink);

			if (SUCCEEDED(hr))
			{
				hr = m_pBorder->CombineWithGeometry(
					m_pCircleGeometry2,
					D2D1_COMBINE_MODE::D2D1_COMBINE_MODE_EXCLUDE,
					NULL,
					NULL,
					pGeometrySink
				);
			}

			if (SUCCEEDED(hr))
			{
				hr = pGeometrySink->Close();
			}

			//SafeRelease(&pGeometrySink);
		}
	}
	if (this->Background)
	{
		this->Background->Refresh(pRT);
		//this->pRT->FillGeometry(m_pPathGeometryUnion, *this->Background);
		pRT->DrawGeometry(m_pBorder, *this->Background);

		pCompatibleRenderTarget->FillGeometry(m_pCircleGeometry2, *this->Background);
	}
	

	
	pCompatibleRenderTarget->EndDraw();

	pCompatibleRenderTarget->EndDraw();
	ID2D1Bitmap* bmp = NULL;
	pCompatibleRenderTarget->GetBitmap(&bmp);

	//pRT->DrawBitmap(bmp, rc);
	CDirectUI_Rect rc_dst = rc;
	CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);
	bmp->Release();
	pCompatibleRenderTarget->Release();

	if (this->m_Child != nullptr)
	{
		this->m_Child->OnRender(pRT, calculate_dpi);
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

void CBorder::SetCornerRadius(CDirectUI_CornerRadius& data)
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
