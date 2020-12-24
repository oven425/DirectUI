#pragma once
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CContentControl : public CControl
		{
		public:
			unique_ptr<CControl> m_Child;
		protected:
			void OnRender(ID2D1HwndRenderTarget* pRT) override;
		};

	}

}

