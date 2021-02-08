#pragma once
#include "CControl.h"
#include "CD2D_Font.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CTextBlock : public CControl
		{
		public:
			void SetText(const wchar_t* data);
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			void Arrange(float x, float y, float width, float height) override;
			shared_ptr<CD2D_Brush> Foreground;
			shared_ptr<CD2D_Font> Font;
		protected:
			wstring m_Text;
		};
	}
}


