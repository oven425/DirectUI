#pragma once
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CContentControl : public CControl
		{
		public:
			CContentControl();
			virtual void OnRender(ID2D1RenderTarget* pRT) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;

			void SetPadding(shared_ptr<CDirectUI_Thinkness> data);
			shared_ptr<CDirectUI_Thinkness> GetPadding();
			__declspec(property(get = GetPadding, put = SetPadding)) shared_ptr<CDirectUI_Thinkness> Padding;

			virtual void SetChild(shared_ptr<UIElement> data);
			bool HitTest(int x, int y, vector<shared_ptr<UIElement>>& childs) override;
			void SetRoot(weak_ptr<UIElement> data) override;
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			shared_ptr<UIElement> m_Child;
			static shared_ptr<DependencyProperty<shared_ptr<CDirectUI_Thinkness>>> PaddingProperty;
		};

	}

}

