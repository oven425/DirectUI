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
	}
	break;
	case WM_LBUTTONUP:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
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
	this->OnRender(this->pRT);
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

void CWindow::OnRender(ID2D1RenderTarget* pRT)
{	
	this->pRT->BeginDraw();
	this->pRT->Clear(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f));
	//CContentControl::OnRender(this->pRT);

	
	HRESULT hr = S_OK;
	ID2D1GeometrySink *pGeometrySink = NULL;

	// Create the first ellipse geometry to merge.
	const D2D1_ELLIPSE circle1 = D2D1::Ellipse(
		D2D1::Point2F(75.0f, 75.0f),
		50.0f,
		50.0f
	);
	//ID2D1RectangleGeometry* m_pCircleGeometry1 = NULL;
	ID2D1RectangleGeometry* m_pCircleGeometry2 = NULL;
	ID2D1PathGeometry* m_pPathGeometryUnion = NULL;
	//hr = m_pD2DFactory->CreateEllipseGeometry(
	//	circle1,
	//	&m_pCircleGeometry1
	//);
	ID2D1PathGeometry* m_pBorder = NULL;
	hr = m_pD2DFactory->CreatePathGeometry(&m_pBorder);
	if (SUCCEEDED(hr))
	{

		ID2D1GeometrySink *pSink = NULL;

		hr = m_pBorder->Open(&pSink);
		if (SUCCEEDED(hr))
		{
			pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

			pSink->BeginFigure(
				D2D1::Point2F(20, 10),
				D2D1_FIGURE_BEGIN_FILLED
			);
			pSink->AddLine(D2D1::Point2F(90, 10));

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
			pSink->AddLine(D2D1::Point2F(20, 100));
			pSink->AddArc(
				D2D1::ArcSegment(
					D2D1::Point2F(10, 90), // end point
					D2D1::SizeF(10, 10),
					0.0f, // rotation angle
					D2D1_SWEEP_DIRECTION_CLOCKWISE,
					D2D1_ARC_SIZE_SMALL
				));
			pSink->AddLine(D2D1::Point2F(10, 20));
			pSink->AddArc(
				D2D1::ArcSegment(
					D2D1::Point2F(20, 10), // end point
					D2D1::SizeF(10, 10),
					0.0f, // rotation angle
					D2D1_SWEEP_DIRECTION_CLOCKWISE,
					D2D1_ARC_SIZE_SMALL
				));
			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		}

		hr = pSink->Close();
	}

	if (SUCCEEDED(hr))
	{
		// Create the second ellipse geometry to merge.
		const D2D1_ELLIPSE circle2 = D2D1::Ellipse(
			D2D1::Point2F(125.0f, 75.0f),
			50.0f,
			50.0f
		);

		//hr = m_pD2DFactory->CreateEllipseGeometry(circle2, &m_pCircleGeometry2);

		D2D1_RECT_F  rc2 = D2D1::RectF(20, 20, 90, 90);
		hr = m_pD2DFactory->CreateRectangleGeometry(rc2, &m_pCircleGeometry2);
	}


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
	this->Background->Refresh(pRT);
	this->pRT->FillGeometry(m_pPathGeometryUnion, *this->Background);
	//pRT->DrawGeometry(m_pBorder, *this->Background);
	this->pRT->EndDraw();
}

void CWindow::SetTitle(const wchar_t* data)
{
	::SetWindowTextW(this->m_hWnd, data);
}