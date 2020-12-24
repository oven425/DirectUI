#pragma once
#include "CContentControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CBorder : public CContentControl
		{
		public:
			CBorder();
			CBorder(const CBorder& data);
			CBorder(const CBorder&& data);
			const CBorder operator=(const CBorder&& data) { return *this; }
			const CBorder operator=(const CBorder& data) { return *this; }
			unique_ptr<CD2D_Brush> BorderBrush;
			int BorderThickness = 0;
			int CornerRadius = 0;
			void Measure(int width, int height);

		protected:
			void OnSize(int width, int height);
			void OnRender(ID2D1HwndRenderTarget* pRT) override;
		};
	}
}


