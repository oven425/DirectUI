#pragma once
#include <vector>
#include <functional>
using namespace std;

#include <Windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>
#include "CContentControl.h"
#include "CDirectUI_CornerRadius.h"
#include "CDirectUI_MouseManager.h"
#include <d2d1.h>

namespace DirectUI
{
	namespace Control
	{
		struct DragFilesArgs
		{
			vector<wstring> files;
		};
		struct mouseevent_storage
		{
			shared_ptr<CControl> leftbutton;
			shared_ptr<CControl> mouseon;
		};
		class __declspec(dllexport) CWindow :public CContentControl
		{
		public:
			bool Init(HWND hwnd);
			void SetTitle(const wchar_t* data);
			void SetAllowDropFiles(bool data);
			std::function<void(const shared_ptr<CControl> sender, const DragFilesArgs& args)> DragHandler;
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
			bool HitTest(int x, int y, vector<shared_ptr<CControl>>& childs) override;
			HWND m_hWnd = NULL;
		private:
			static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
			mouseevent_storage m_MouseStorage;
			bool m_TrackMouse = false;
		protected:
			void ReDraw();
			ID2D1HwndRenderTarget* pRT = NULL;
		};
	}
}