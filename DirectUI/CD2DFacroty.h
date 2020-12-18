#pragma once
#include <d2d1.h>
namespace DirectUI
{
	namespace D2D
	{
		class __declspec(dllexport) CD2DFacroty
		{
		protected:
			ID2D1Factory* pD2DFactory = NULL;
		public:
			bool Init(HWND hwnd);
			
		};
	}
}


