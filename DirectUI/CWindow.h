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
			
		protected:
			void OnSize(int width, int height);
			void OnRender();
			HWND m_hWNd = NULL;
			CControl m_Children;
		private:
			static LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
		};


	}
}