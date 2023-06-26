#pragma once
#include <atlstr.h>
#include "Lazy.h"

#include "UIElement.h"
#include "DependecyProperty.h"


class Window
{
public:
	static Window* Mount(HWND hwnd)
	{
		auto window = new Window(hwnd);
		
		return window;
	}
private:
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto window = (Window*)dwRefData;
		switch (uMsg)
		{
		case WM_SIZE:
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);
			window->OnSize(width, height);
		}
		break;
		case WM_PAINT:
		{
			window->OnPaint();
		}
		break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	void OnSize(UINT width, UINT height)
	{
		CString str;
		str.Format(_T("width:%d height:%d\r\n"), width, height);
		::OutputDebugString(str);
		D2D1_SIZE_U sz;
		sz.width = width;
		sz.height = height;
		auto hr = m_pRenderTarget->Resize(sz);
	}

	void OnPaint()
	{
		static const WCHAR sc_helloWorld[] = L"Hello, World!";

		// Retrieve the size of the render target.
		D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();

		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Red));

		//m_pRenderTarget->DrawText(
		//	sc_helloWorld,
		//	ARRAYSIZE(sc_helloWorld) - 1,
		//	m_pTextFormat,
		//	D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		//	m_pBlackBrush
		//);

		auto hr = m_pRenderTarget->EndDraw();

		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			//DiscardDeviceResources();
		}
	}

	Window(HWND hwnd)
		: m_hWnd(hwnd)
	{
		SetWindowSubclass(this->m_hWnd, WinProc, 0, (DWORD_PTR)this);
		RECT rc;
		GetClientRect(this->m_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		auto hr = m_D2DFactory.Value()->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(this->m_hWnd, size),
			&m_pRenderTarget
		);
		this->OnPaint();
	}
protected:
	UIElement Content;

private:
	static Lazy<CComPtr<ID2D1Factory>> m_D2DFactory;
	CComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
	HWND m_hWnd = NULL;
	DependecyProperty<Brush> Background;
};



