#include "pch.h"
#include "Graphic.h"


CComPtr<ID2D1Factory> Graphic::m_GraphicsFactory;
once_flag Graphic::m_Once;
Graphic::Graphic()
{
	
	std::call_once(Graphic::m_Once, [] {
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &Graphic::m_GraphicsFactory);
	});
}