#pragma once
#include "CContentControl.h"


namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CButton : public CContentControl
		{
		public:
			void SetContent(const wchar_t* data);
			void SetContent(shared_ptr<CControl> data);
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			void Arrange(float x, float y, float width, float height) override;
		};

	}
}

