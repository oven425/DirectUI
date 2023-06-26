#include "pch.h"
#include "UIElement.h"
#include <dwrite.h>
Lazy<CComPtr<ID2D1Factory>> Control::m_D2DFactory([] {
	CComPtr<ID2D1Factory> ff = nullptr;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &ff);
	return ff;
	});

Lazy<CComPtr<IDWriteFactory>> Control::m_DWriteFactory([] {
	CComPtr<IDWriteFactory> pDWriteFactory_ = nullptr;
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory_));
		return pDWriteFactory_;
	});
