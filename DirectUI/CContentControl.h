#pragma once
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CContentControl : public CControl
		{
		public:
			virtual void OnRender(ID2D1RenderTarget* pRT) override;
			//virtual void Arrange(float x, float y, float width, float height) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void SetPadding(CDirectUI_Thinkness& data);
			virtual void SetChild(shared_ptr<CControl> data);
			bool HitTest(int x, int y, vector<shared_ptr<CControl>>& childs) override;
			void SetRoot(weak_ptr<CControl> data) override;
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			CDirectUI_Thinkness m_Padding;
			shared_ptr<CControl> m_Child;
			
		};

	}

}

