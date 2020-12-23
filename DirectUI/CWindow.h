#pragma once
#include <Windows.h>
#include <commctrl.h>
#include "CControl.h"
#include <d2d1.h>
namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CWindow :public CControl
		{
			//friend class CControl;
		public:
			bool Init(HWND hwnd);
		protected:
			void OnSize(int width, int height);
			void OnRender();
			HWND m_hWNd = NULL;
			unique_ptr<CControl> m_Children;
		private:
			static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
		protected:
			ID2D1Factory* pD2DFactory = NULL;
			ID2D1HwndRenderTarget* pRT = NULL;
		};
	}
}