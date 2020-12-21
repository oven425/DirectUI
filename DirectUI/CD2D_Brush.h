#pragma once
#include <d2d1.h>

namespace DirectUI
{
	class __declspec(dllexport) CD2D_Brush
	{
		virtual void Refresh(ID2D1HwndRenderTarget* target) {}

	};
}


