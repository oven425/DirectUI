#pragma once
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
			void Measure(int width, int height);

		protected:
			void OnRender(ID2D1HwndRenderTarget* pRT) override;
		};
	}
}


