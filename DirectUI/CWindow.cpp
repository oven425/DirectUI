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
		ww->Invalidate();
	}
	break;
	case WM_MOUSELEAVE:
	case WM_MOUSEMOVE:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		//char msg[256] = { 0 };
		//::sprintf_s(msg, "mouse move x:%d y%d\r\n", xPos, yPos);
		//::OutputDebugStringA(msg);
		if (uMsg == WM_MOUSELEAVE)
		{
			ww->m_TrackMouse = false;
		}
		else if (ww->m_TrackMouse == false)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.hwndTrack = ww->m_hWnd;
			tme.dwHoverTime = 100;
			BOOL bb = ::TrackMouseEvent(&tme);
			ww->m_TrackMouse == true;
		}
		vector<shared_ptr<UIElement>> childs;
		if (ww->HitTest(xPos, yPos, childs) == true)
		{
			MouseMoveArgs mouseargs = { 0 };
			mouseargs.X = xPos;
			mouseargs.Y = yPos;
			for (auto oo : childs)
			{
				oo->OnMouseMove(mouseargs);
				if (oo->MouseMoveHandler)
				{
					oo->MouseMoveHandler(oo, mouseargs);
				}
			}
			if (ww->m_MouseStorage.leftbutton && ww->m_MouseStorage.leftbutton->GetCaptureMouse() == true)
			{
				
				if (ww->m_MouseStorage.mouseon != childs.back() && ww->m_MouseStorage.leftbutton->GetIsMouseOver() == true)
				{
					ww->m_MouseStorage.leftbutton->OnMouseLeave(mouseargs);
				}
				else if(ww->m_MouseStorage.mouseon == childs.back() && ww->m_MouseStorage.leftbutton->GetIsMouseOver() == false)
				{
					ww->m_MouseStorage.leftbutton->OnMouseEnter(mouseargs);
				}
				else if(ww->m_MouseStorage.leftbutton != childs.back())
				{
					ww->m_MouseStorage.leftbutton->OnMouseMove(mouseargs);
				}
			}
			else if (!ww->m_MouseStorage.mouseon)
			{
				ww->m_MouseStorage.mouseon = childs.back();
				ww->m_MouseStorage.mouseon->OnMouseEnter(mouseargs);
				if (ww->m_MouseStorage.mouseon->MouseEnterHandler)
				{
					ww->m_MouseStorage.mouseon->MouseEnterHandler(ww->m_MouseStorage.mouseon, mouseargs);
				}
			}
			else if (ww->m_MouseStorage.mouseon && ww->m_MouseStorage.mouseon != childs.back())
			{
				ww->m_MouseStorage.mouseon->OnMouseLeave(mouseargs);
				if (ww->m_MouseStorage.mouseon->MouseLeaveHandler)
				{
					ww->m_MouseStorage.mouseon->MouseLeaveHandler(ww->m_MouseStorage.mouseon, mouseargs);
				}
				ww->m_MouseStorage.mouseon = childs.back();
				ww->m_MouseStorage.mouseon->OnMouseEnter(mouseargs);
				if (ww->m_MouseStorage.mouseon->MouseEnterHandler)
				{
					ww->m_MouseStorage.mouseon->MouseEnterHandler(ww->m_MouseStorage.mouseon, mouseargs);
				}
			}

		}
		//ww->Invalidate();
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		::SetCapture(ww->m_hWnd);
		vector<shared_ptr<UIElement>> childs;
		if (ww->HitTest(xPos, yPos, childs) == true)
		{
			MouseLeftButtonDownArgs mouseargs = { 0 };
			mouseargs.X = xPos;
			mouseargs.Y = yPos;
			ww->m_MouseStorage.leftbutton = childs.back();
			for (auto oo : childs)
			{
				oo->OnMouseLeftButtonDown(mouseargs);
				if (oo->MouseLeftButtonDownHandler)
				{
					oo->MouseLeftButtonDownHandler(oo, mouseargs);
				}
			}
		}
		//ww->Invalidate();
	}
	break;
	case WM_LBUTTONUP:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		vector<shared_ptr<UIElement>> childs;
		if (ww->HitTest(xPos, yPos, childs) == true)
		{
			MouseLeftButtonUpArgs mouseargs = { 0 };
			mouseargs.X = xPos;
			mouseargs.Y = yPos;
			for (auto oo : childs)
			{
				oo->OnMouseLeftButtonUp(mouseargs);
				if (oo->MouseLeftButtonUpHandler)
				{
					oo->MouseLeftButtonUpHandler(oo, mouseargs);
				}
			}
			if (ww->m_MouseStorage.leftbutton && ww->m_MouseStorage.leftbutton == childs.back())
			{
				if (childs.back()->MouseClickHandler)
				{
					childs.back()->MouseClickHandler(childs.back(), MouseClickArgs());
				}
			}
			else if(ww->m_MouseStorage.leftbutton)
			{
				ww->m_MouseStorage.leftbutton->OnMouseLeftButtonUp(mouseargs);
			}
		}
		ww->m_MouseStorage.leftbutton = nullptr;
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
		float dpiscale = (float)(dpi / 96.0);
		ww->OnSize(width, height, dpiscale);
	}
	break;
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;
		UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
		DragFilesArgs dragfiles;
		for (UINT i = 0; i < nFiles; i++)
		{
			wchar_t szFileName[MAX_PATH + 1] = { 0 };
			DragQueryFile(hDrop, i, szFileName, MAX_PATH);
			dragfiles.files.push_back(szFileName);
			::OutputDebugStringW(szFileName);
		}
		::DragFinish(hDrop);
		if (ww->DragHandler)
		{
			ww->DragHandler(static_pointer_cast<CControl>(ww->shared_from_this()), dragfiles);
		}
	}
	break;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

bool CWindow::Init(HWND hwnd)
{
	this->m_hWnd = hwnd;
	

	SetWindowSubclass(this->m_hWnd, WinProc, 0, (DWORD_PTR)this);
	RECT rc;
	GetClientRect(hwnd, &rc);
	

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
#ifdef D2D1_Ex
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_1;

	hr = D3D11CreateDevice(
		nullptr,                    // specify null to use the default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		creationFlags,              // optionally set debug and Direct2D compatibility flags
		featureLevels,              // list of feature levels this app can support
		ARRAYSIZE(featureLevels),   // number of possible feature levels
		D3D11_SDK_VERSION,
		&device,                    // returns the Direct3D device created
		&m_featureLevel,            // returns feature level of device created
		&context                    // returns the device immediate context
	);
	
	hr = device.As(&dxgiDevice);

	D2D1_FACTORY_OPTIONS options{};
	
	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		options,
		&factory);
	
	hr = factory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice);

	
	m_d2dDevice->CreateDeviceContext(
		D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
		&m_d2dContext
	);


	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;                           // use automatic sizing
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
	swapChainDesc.Flags = 0;
	
	hr = dxgiDevice->GetAdapter(&dxgiAdapter);

	
	hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
	
	
	hr = dxgiFactory->CreateSwapChainForHwnd(
		device.Get(),
		this->m_hWnd,
		&swapChainDesc,
		nullptr,    // allow on all displays
		m_dxgioutput.Get(),
		&m_swapChain
	);

	hr = dxgiDevice->SetMaximumFrameLatency(1);
	
	hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));


	D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96, 96);

	
	m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
	
	hr = m_d2dContext->CreateBitmapFromDxgiSurface(
		dxgiBackBuffer.Get(),
		&bitmapProperties,
		&m_d2dTargetBitmap
	);

	m_d2dContext->SetTarget(m_d2dTargetBitmap.Get());
#endif
	

	

	
	float width = (float)(rc.right - rc.left);
	float height = (float)(rc.bottom - rc.top);

	hr = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hwnd,
			D2D1::SizeU((width, height))
		),
		&pRT
	);
	auto owner = static_pointer_cast<CControl>(this->shared_from_this());
	this->m_Root = owner;
	this->SetRoot(this->m_Root);

	UINT dpi = ::GetDpiForWindow(this->m_hWnd);
	//dpi = 96;
	float dpiscale = (float)(dpi / 96.0);
	this->OnSize(width, height, dpiscale);
	return true;
}

bool CWindow::HitTest(int x, int y, vector<shared_ptr<UIElement>>& childs)
{
	float x_dpi = x / this->m_DpiScale;
	float y_dpi = y / this->m_DpiScale;
	return ::CContentControl::HitTest(x_dpi, y_dpi, childs);
}

void CWindow::OnSize(float width, float height, float dpiscale)
{
	//this->pRT->Resize(D2D1::SizeU(width, height));
	//CContentControl::OnSize(width, height, dpiscale);

	this->Measure(CDirectUI_Size(width / dpiscale, height / dpiscale), this->pRT);
	this->Arrange(CDirectUI_Rect(0, 0, width / dpiscale, height / dpiscale));
}
#ifdef D2D1_Ex
bool CWindow::createD3DTexture(void* bytes, int width, int height)
{
	D3D11_TEXTURE2D_DESC desc;

	desc.Width = width;

	desc.Height = height;

	desc.MipLevels = 1;

	desc.ArraySize = 1;

	desc.Format = DXGI_FORMAT::DXGI_FORMAT_NV12;

	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	desc.SampleDesc.Count = 1;

	desc.SampleDesc.Quality = 0;

	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;

	desc.CPUAccessFlags = 0;

	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = bytes;

	data.SysMemPitch = width;

	HRESULT result = device->CreateTexture2D(&desc, &data, &d3d_texture);

	return (result == S_OK) ? true : false;
}
#endif

#include "File.h"
#include "CD2D_SolidColorBrush.h"
void CWindow::OnRender(ID2D1RenderTarget* pRT)
{	
#ifdef D2D1_Ex
	IO::File::ReadAllBytes(L"");
	RECT rc;
	GetClientRect(this->m_hWnd, &rc);
	ComPtr<ID2D1SolidColorBrush> pBlackBrush;
	m_d2dContext->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&pBlackBrush
	);
	m_d2dContext->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	m_d2dContext->BeginDraw();

	m_d2dContext->DrawRectangle(
		D2D1::RectF(
			rc.left + 100.0f,
			rc.top + 100.0f,
			rc.right - 100.0f,
			rc.bottom - 100.0f),
		pBlackBrush.Get());

	m_d2dContext->EndDraw();
	DXGI_PRESENT_PARAMETERS parameters = { 0 };
	HRESULT hr = m_swapChain->Present1(1, 0, &parameters);
#else
	if (pRT != NULL)
	{
		this->pRT->BeginDraw();
		this->pRT->Clear(D2D1::ColorF(D2D1::ColorF::Red, 1.0f));
	

		//pRT->PushAxisAlignedClip(
		//	D2D1::RectF(20, 20, 120, 120),
		//	D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
		//);

		//Direct2D::CD2D_SolidColorBrush br = Direct2D::CD2D_SolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green));
		//br.Refresh(pRT);
		//////pRT->FillRectangle(D2D1::RectF(10, 10, 30, 30), br);
		////pRT->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(50, 50), 50, 50), br, 2);
		////pRT->PopAxisAlignedClip();

		//pRT->PushAxisAlignedClip(
		//	D2D1::RectF(40, 40, 100, 100),
		//	D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
		//);

		//pRT->DrawRectangle(D2D1::RectF(10, 10, 100, 100), br, 5);
		//pRT->PopAxisAlignedClip();
		//pRT->PopAxisAlignedClip();

		CContentControl::OnRender(this->pRT);

		this->pRT->EndDraw();
	}


#endif
}

void CWindow::SetTitle(const wchar_t* data)
{
	::SetWindowTextW(this->m_hWnd, data);
}

void CWindow::SetAllowDropFiles(bool data)
{
	DragAcceptFiles(this->m_hWnd, data==true?TRUE:FALSE);
}

void CWindow::Invalidate()
{
	this->OnRender(this->pRT);
}

void CWindow::InvalidateArrange()
{
	RECT rc;
	GetClientRect(this->m_hWnd, &rc);
	float width = (float)(rc.right - rc.left);
	float height = (float)(rc.bottom - rc.top);
	UINT dpi = ::GetDpiForWindow(this->m_hWnd);
	float dpiscale = (float)(dpi / 96.0);

	this->Arrange(CDirectUI_Rect(0, 0, width / dpiscale, height / dpiscale));
}

void CWindow::InvalidateMeasurce()
{
	RECT rc;
	GetClientRect(this->m_hWnd, &rc);
	float width = (float)(rc.right - rc.left);
	float height = (float)(rc.bottom - rc.top);
	UINT dpi = ::GetDpiForWindow(this->m_hWnd);
	float dpiscale = (float)(dpi / 96.0);

	this->Measure(CDirectUI_Size(width / dpiscale, height / dpiscale), this->pRT);
}