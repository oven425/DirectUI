#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "CContentControl.h"
#include <d2d1.h>
namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CWindow :public CContentControl
		{
			//friend class CControl;
		public:
			bool Init(HWND hwnd);
			void SetTitle(const wchar_t* data);
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
			HWND m_hWnd = NULL;
			shared_ptr<CControl> m_Children;
		private:
			static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
		protected:
			void ReDraw();
			ID2D1Factory* pD2DFactory = NULL;
			ID2D1HwndRenderTarget* pRT = NULL;
		};
	}
}