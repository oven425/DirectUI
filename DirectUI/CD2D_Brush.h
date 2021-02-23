#pragma once
#include <memory>
using namespace std;
#include <d2d1.h>
#include "CDirectUI_Color.h"

namespace DirectUI
{
	namespace Direct2D
	{
		class __declspec(dllexport) CD2D_Brush
		{
		public:
			virtual void Refresh(ID2D1RenderTarget* target) {}
			virtual operator ID2D1Brush*() { return NULL; }
			virtual void Release() {};
		};
	}
}


