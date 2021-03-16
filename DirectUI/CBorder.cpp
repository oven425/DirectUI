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


void CBorder::OnRender(ID2D1RenderTarget* pRT)
{
	HRESULT hr = S_OK;
	//ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	//HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);
	//pCompatibleRenderTarget->BeginDraw();
	this->CreateRenderBuf(pRT, this->DesiredSize);
	CDirectUI_Rect rc = CDirectUI_Rect(0, 0, this->DesiredSize.width, this->DesiredSize.height);


	CDirectUI_CornerRadius cornerradius = this->m_CornerRadius;

	//CDirectUI_Thinkness m_BorderThickness(10);
	CDirectUI_Thinkness borderthickness = this->m_BorderThickness;

	ID2D1GeometrySink *pGeometrySink = NULL;


	ID2D1PathGeometry* m_pPathGeometryUnion = NULL;
	CDirectUI_Thinkness thinkness = borderthickness / 2;
	ID2D1PathGeometry* m_pBorder = this->BuildPath(rc, cornerradius - thinkness, thinkness);

	CDirectUI_Thinkness thinkness1 = borderthickness / 2;
	ID2D1PathGeometry* m_pCircleGeometry2 = this->BuildPath(rc+ borderthickness, cornerradius - thinkness, -thinkness1);



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
	if (this->m_BorderBrush)
	{
		this->m_BorderBrush->Refresh(this->m_pRenderBuf);
		this->m_pRenderBuf->FillGeometry(m_pPathGeometryUnion, *this->m_BorderBrush);
	}
	if (this->m_Background)
	{
		this->m_Background->Refresh(this->m_pRenderBuf);

		//pCompatibleRenderTarget->DrawGeometry(m_pPathGeometryUnion, *this->Background);

		this->m_pRenderBuf->FillGeometry(m_pCircleGeometry2, *this->m_Background);
	}
	

	if (this->m_Child)
	{
		this->m_Child->OnRender(this->m_pRenderBuf);
	}

	::CControl::OnRender(pRT);
}

//void CBorder::Arrange(float x, float y, float width, float height)
//{
//	CDirectUI_Size border_sz = CDirectUI_Size(width, height) + this->m_Margin;
//	if (this->m_Child)
//	{
//		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
//		{
//			this->DesiredSize.width = border_sz.GetWidth();
//		}
//		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
//		{
//			this->DesiredSize.height = border_sz.GetHeight();
//		}
//		CControl::Arrange(x, y, width, height);
//		
//		CDirectUI_Rect rc = this->DesiredSize;
//		rc = rc + this->m_BorderThickness;
//		rc = rc + this->m_Padding;
//		
//		this->m_Child->Arrange(rc.GetX(), rc.GetY(), rc.GetWidth(), rc.GetHeight());
//	}
//	else
//	{
//		CControl::Arrange(x, y, width, height);
//	}
//}

void CBorder::Arrange(const CDirectUI_Rect& data)
{
	CDirectUI_Size border_sz = data + this->m_Margin;
	if (this->m_Child)
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = border_sz.GetWidth();
		}
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = border_sz.GetHeight();
		}
		CControl::Arrange(data);
		
		CDirectUI_Rect rc = this->DesiredSize;
		rc = rc + this->m_BorderThickness;
		rc = rc + this->m_Padding;
		
		this->m_Child->Arrange(data);
	}
	else
	{
		CControl::Arrange(data);
	}
}

void CBorder::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Size border_sz = data + this->m_Margin;
	if (this->m_Child)
	{
		CDirectUI_Size child_sz = border_sz + this->m_Padding + this->m_BorderThickness;
		this->m_Child->Measure(child_sz, pRT);
		
		//else
		{
			this->DesiredSize.width = this->m_Child->DesiredSize.width + this->m_BorderThickness.GetLeft() + this->m_BorderThickness.GetRight();
		}
		
		//else
		{
			this->DesiredSize.height = this->m_Child->DesiredSize.height + this->m_BorderThickness.GetTop() + this->m_BorderThickness.GetBottom();
		}

	}
	else
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = border_sz.GetWidth();
		}
		else
		{
			this->DesiredSize.width = this->m_BorderThickness.GetLeft() + this->m_BorderThickness.GetRight();
		}
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = border_sz.GetHeight();
		}
		else
		{
			this->DesiredSize.height = this->m_BorderThickness.GetTop() + this->m_BorderThickness.GetBottom();
		}

	}
}

void CBorder::SetCornerRadius(CDirectUI_CornerRadius& data)
{
	if (this->m_CornerRadius != data)
	{
		this->m_CornerRadius = data;
		this->Release();
	}
}

void CBorder::SetBorderBrush(shared_ptr<Direct2D::CD2D_Brush> data)
{
	if (this->m_BorderBrush)
	{
		this->m_BorderBrush->Release();
	}
	this->m_BorderBrush = data;
}

void CBorder::SetBorderThickness(const CDirectUI_Thinkness& data)
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
