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
		protected:
			void OnSize(int width, int height) override;
			void OnRender(ID2D1HwndRenderTarget* pRT) override;
		};

	}

}

