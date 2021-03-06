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
			void SetContent(const wchar_t* data);
			void SetContent(shared_ptr<CControl> data);
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
			void OnMouseEnter(const MouseMoveArgs& args) override;
			void OnMouseLeave(const MouseMoveArgs& args) override;
			void OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args) override;
			void OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args) override;
			bool HitTest(int x, int y, vector<shared_ptr<UIElement>>& childs) override;
		private:
			shared_ptr<Direct2D::CD2D_Brush> m_NormalBK;
			shared_ptr<Direct2D::CD2D_Brush> m_NormalBr;
			shared_ptr<Direct2D::CD2D_Brush> m_HoverBK;
			shared_ptr<Direct2D::CD2D_Brush> m_HoverBr;
			shared_ptr<Direct2D::CD2D_Brush> m_PressBK;
			shared_ptr<Direct2D::CD2D_Brush> m_PressBr;
			shared_ptr<Direct2D::CD2D_Brush> m_DisableBK;
			shared_ptr<Direct2D::CD2D_Brush> m_DisableBr;
			shared_ptr<CBorder> m_Template;
		};

	}
}

