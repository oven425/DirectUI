#pragma once
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CTextBlock:public CControl
		{
		public:
			CD2D_Brush Foreground;
			void SetText(const wchar_t* data) { this->m_Text = data; }
			void OnRender(ID2D1HwndRenderTarget* pRT) override;
		protected:
			wstring m_Text = L"";
		};
	}
}


