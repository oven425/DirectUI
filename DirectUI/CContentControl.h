#pragma once
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CContentControl : public CControl
		{
		public:
			shared_ptr<CControl> m_Child;
		public:
			virtual void OnRender(ID2D1HwndRenderTarget* pRT) override;
			virtual void Arrange(double x, double y, double width, double height) override;
			virtual void Measure(double width, double height) override;
		protected:
			void OnSize(double width, double height, double dpiscale) override;
		};

	}

}

