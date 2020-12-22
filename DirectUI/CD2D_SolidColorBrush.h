#pragma once
#include "CD2D_Brush.h"

namespace DirectUI
{
	class __declspec(dllexport) CD2D_SolidColorBrush: public CD2D_Brush
	{
	public:
		CD2D_SolidColorBrush(const D2D1_COLOR_F& color);
		virtual ~CD2D_SolidColorBrush();
		virtual void Refresh(ID2D1HwndRenderTarget* target);
		operator ID2D1Brush*() { return this->m_pBrush; }
	protected:
		void Release();
		ID2D1SolidColorBrush* m_pBrush = NULL;
		D2D1_COLOR_F m_Color;
	};

}

