#pragma once
#include "CD2D_Brush.h"

namespace DirectUI
{
	class __declspec(dllexport) CD2D_SolidColorBrush: public CD2D_Brush
	{
	public:
		//ID2D1SolidColorBrush* opertor() { return NULL; }
	protected:
		ID2D1SolidColorBrush* m_pBrush = NULL;
	};

}

