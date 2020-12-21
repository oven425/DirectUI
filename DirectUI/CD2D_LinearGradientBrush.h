#pragma once
#include "CD2D_Brush.h"

namespace DirectUI
{
	class __declspec(dllexport) CD2D_LinearGradientBrush :public CD2D_Brush
	{
	protected:
		ID2D1LinearGradientBrush* m_pBrush = NULL;
	};
}


