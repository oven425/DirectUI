#pragma once
#include <d2d1.h>

class Graphic
{
public:
	static Graphic* Mount()
	{
		return nullptr;
	}
private:
	Graphic();
	static CComPtr<ID2D1Factory> m_GraphicsFactory;
};

