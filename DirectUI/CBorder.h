#pragma once
#include "CDirectUI_Thinkness.h"
#include "CContentControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CBorder : public CContentControl
		{
		public:
			shared_ptr<CD2D_Brush> BorderBrush;
			int BorderThickness = 0;
			int CornerRadius = 0;
			virtual void Arrange(float x, float y, float width, float height);
			virtual void Measure(float width, float height, ID2D1RenderTarget* pRT);
		protected:
			void OnRender(ID2D1RenderTarget* pRT) override;
		};
	}
}


