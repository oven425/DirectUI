#include "pch.h"
#include "Window.h"
Lazy<CComPtr<ID2D1Factory>> Window::m_D2DFactory([] {
	CComPtr<ID2D1Factory> ff = nullptr;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &ff);
	return ff;
	});