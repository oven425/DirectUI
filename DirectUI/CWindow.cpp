#include "pch.h"
#include "CWindow.h"
using namespace DirectUI;
using namespace Control;

LRESULT CWindow::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	CWindow* ww = (CWindow*)dwRefData;
	
	switch (uMsg)
	{
	case WM_ERASEBKGND:
	case WM_PAINT:
	{
		ww->ReDraw();
	}
	break;
	case WM_MOUSEHOVER:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_MOUSEMOVE:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		::SetCapture(ww->m_hWnd);
	}
	break;
	case WM_LBUTTONUP:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		::ReleaseCapture();
	}
	break;
	case WM_SIZING:
	{
		RECT* rc = (RECT*)lParam;
		if (ww->m_MinWidth > 0)
		{
			int w = rc->right - rc->left;
			if (ww->m_MinWidth > w)
			{
				rc->right = rc->left + ww->m_MinWidth;
			}
		}
		if (ww->m_MaxWidth > 0)
		{
			int w = rc->right - rc->left;
			if (ww->m_MaxWidth < w)
			{
				rc->right = rc->left + ww->m_MaxWidth;
			}
		}
		if (ww->m_MinHeight > 0)
		{
			int h = rc->bottom - rc->top;
			if (ww->m_MinHeight > h)
			{
				rc->bottom = rc->top + ww->m_MinHeight;
			}
		}
		if (ww->m_MaxHeight > 0)
		{
			int h = rc->bottom - rc->top;
			if (ww->m_MinHeight < h)
			{
				rc->bottom = rc->top + ww->m_MinHeight;
			}
		}
	}
	break;
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		UINT dpi = ::GetDpiForWindow(hWnd);
		float dpiscale = dpi / 96.0;
		ww->OnSize(width, height, dpiscale);
	}
	break;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

void CWindow::ReDraw()
{
	this->OnRender(this->pRT, true);
}

bool CWindow::Init(HWND hwnd)
{
	this->m_hWnd = hwnd;
	


	SetWindowSubclass(this->m_hWnd, WinProc, 0, (DWORD_PTR)this);

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	RECT rc;
	GetClientRect(hwnd, &rc);

	UINT dpi = ::GetDpiForWindow(this->m_hWnd);
	float dpiscale = dpi/96.0;
	float width = rc.right - rc.left;
	//width = width / dpiscale;
	float height = rc.bottom - rc.top;
	//height = height / dpiscale;
	//CDirectUI_Rect rc(0, 0, rc.right, rc.bottom);
	//rc = rc / dpiscale;
	// Create a Direct2D render target          
	hr = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hwnd,
			D2D1::SizeU((width/dpi, height/dpi))
		),
		&pRT
	);

	this->OnSize(width, height, dpiscale);
	return true;
}

void CWindow::OnSize(float width, float height, float dpiscale)
{
	this->pRT->Resize(D2D1::SizeU(width/ dpiscale, height/ dpiscale));
	CContentControl::OnSize(width, height, dpiscale);
	this->Measure(width / dpiscale, height / dpiscale, this->pRT);
	this->Arrange(0, 0, width / dpiscale, height / dpiscale);

}

ID2D1PathGeometry* CWindow::BuildPath(CDirectUI_Rect rc, CDirectUI_CornerRadius corner_radius, CDirectUI_Thinkness thinkness)
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

void CWindow::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{	
	this->pRT->BeginDraw();
	this->pRT->Clear(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f));
	CContentControl::OnRender(this->pRT, calculate_dpi);

	//CDirectUI_Rect rc(10, 10, 210, 210);
	//rc = rc / this->m_DpiScale;
	//CDirectUI_CornerRadius m_CornerRadius(100,100,100,20);
	//m_CornerRadius = m_CornerRadius / this->m_DpiScale;

	//CDirectUI_Thinkness m_BorderThickness(10);
	//m_BorderThickness = m_BorderThickness / this->m_DpiScale;
	//HRESULT hr = S_OK;
	//ID2D1GeometrySink *pGeometrySink = NULL;


	//ID2D1PathGeometry* m_pPathGeometryUnion = NULL;
	//CDirectUI_Thinkness thinkness = m_BorderThickness / 2;
	//ID2D1PathGeometry* m_pBorder = this->BuildPath(rc, m_CornerRadius- thinkness, thinkness);

	//CDirectUI_Thinkness thinkness1 = m_BorderThickness / 2;
	//ID2D1PathGeometry* m_pCircleGeometry2 = this->BuildPath(rc+ m_BorderThickness, m_CornerRadius- thinkness, -thinkness1);



	//if (SUCCEEDED(hr))
	//{
	//	//
	//	// Use D2D1_COMBINE_MODE_UNION to combine the geometries.
	//	//
	//	hr = m_pD2DFactory->CreatePathGeometry(&m_pPathGeometryUnion);

	//	if (SUCCEEDED(hr))
	//	{
	//		hr = m_pPathGeometryUnion->Open(&pGeometrySink);

	//		if (SUCCEEDED(hr))
	//		{
	//			hr = m_pBorder->CombineWithGeometry(
	//				m_pCircleGeometry2,
	//				D2D1_COMBINE_MODE::D2D1_COMBINE_MODE_EXCLUDE,
	//				NULL,
	//				NULL,
	//				pGeometrySink
	//			);
	//		}

	//		if (SUCCEEDED(hr))
	//		{
	//			hr = pGeometrySink->Close();
	//		}

	//		//SafeRelease(&pGeometrySink);
	//	}
	//}
	//this->Background->Refresh(pRT);
	////this->pRT->FillGeometry(m_pPathGeometryUnion, *this->Background);
	//pRT->DrawGeometry(m_pBorder, *this->Background);

	//this->pRT->FillGeometry(m_pCircleGeometry2, *this->Background);
	//this->pRT->EndDraw();
}

void CWindow::SetTitle(const wchar_t* data)
{
	::SetWindowTextW(this->m_hWnd, data);
}