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
			CTextBlock() {}
			CTextBlock(const wchar_t* data);
			void SetText(const wchar_t* data);
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
			void SetForeground(shared_ptr<Direct2D::CD2D_Brush> data);
			shared_ptr<Direct2D::CD2D_Font> Font = ::make_shared<Direct2D::CD2D_Font>();
		protected:
			shared_ptr<Direct2D::CD2D_Brush> m_Foreground;
			wstring m_Text;
		};
	}
}


