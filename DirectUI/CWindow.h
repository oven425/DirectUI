#pragma once
#include <Windows.h>
#include <commctrl.h>
#include "CControl.h"
namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CWindow :CControl
		{
		public:
			bool Init(HWND hwnd);
			void OnSize(int width, int height);
		protected:
			HWND m_hWNd = NULL;
			CControl m_Children;
		};


	}
}