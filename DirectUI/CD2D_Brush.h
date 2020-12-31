#pragma once
#include <d2d1.h>

namespace DirectUI
{
	class __declspec(dllexport) CD2D_Brush
	{
	public:
		virtual void Refresh(ID2D1HwndRenderTarget* target) {}
		virtual void Refresh(ID2D1RenderTarget* target) {}
		virtual operator ID2D1Brush*() { return NULL; }
		virtual void Release() {};
	};
}


