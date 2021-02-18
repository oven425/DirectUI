#pragma once
#include <vector>
using namespace std;

#include <Windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>
#include "CContentControl.h"
#include "CDirectUI_CornerRadius.h"
#include <d2d1.h>

namespace DirectUI
{
	namespace Control
	{
		struct CDragFilesArgs
		{
			vector<wstring> files;
		};
		class __declspec(dllexport) CWindow :public CContentControl
		{
			//friend class CControl;
		public:
			bool Init(HWND hwnd);
			void SetTitle(const wchar_t* data);
			void SetAllowDropFiles(bool data);
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			HWND m_hWnd = NULL;
		private:
			static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
		protected:
			void ReDraw();
			
			ID2D1HwndRenderTarget* pRT = NULL;

			ID2D1PathGeometry* BuildPath(CDirectUI_Rect rc, CDirectUI_CornerRadius corner_radius, CDirectUI_Thinkness thinkness);
		};
	}
}