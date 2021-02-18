#pragma once
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CContentControl : public CControl
		{
		public:
			virtual void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			virtual void Arrange(float x, float y, float width, float height) override;
			virtual void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			void SetPadding(CDirectUI_Thinkness& data);
			virtual void SetChild(shared_ptr<CControl> data);
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			CDirectUI_Thinkness m_Padding;
			shared_ptr<CControl> m_Child;
		};

	}

}

