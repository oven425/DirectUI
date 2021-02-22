#pragma once
#include "CContentControl.h"
#include "CBorder.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CButton : public CContentControl
		{
		public:
			CButton();
			void SetContent(const wchar_t* data);
			void SetContent(shared_ptr<CControl> data);
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			void Arrange(float x, float y, float width, float height) override;
			void OnMouseMove(const MouseMoveArgs& args) override;
			void OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args) override;
		private:
			shared_ptr<CD2D_Brush> m_NormalBK;
			shared_ptr<CD2D_Brush> m_NormalBr;
			shared_ptr<CD2D_Brush> m_HoverBK;
			shared_ptr<CD2D_Brush> m_HoverBr;
			shared_ptr<CD2D_Brush> m_PressBK;
			shared_ptr<CD2D_Brush> m_PressBr;
			shared_ptr<CD2D_Brush> m_DisableBK;
			shared_ptr<CD2D_Brush> m_DisableBr;
			shared_ptr<CBorder> m_Template;
		};

	}
}

