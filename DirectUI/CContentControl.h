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
		protected:
			void OnSize(double width, double height, double dpiscale) override;
		};

	}

}

