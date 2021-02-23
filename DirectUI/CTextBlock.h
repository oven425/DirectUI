#pragma once
#include "CD2D_Font.h"


#include "CControl.h"



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
			void SetForeground(shared_ptr<Direct2D::CD2D_Brush> data);
			shared_ptr<Direct2D::CD2D_Font> Font = ::make_shared<Direct2D::CD2D_Font>();
		protected:
			shared_ptr<Direct2D::CD2D_Brush> m_Foreground;
			wstring m_Text;
		};
	}
}


