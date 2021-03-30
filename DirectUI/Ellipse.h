#pragma once
#include "CControl.h"
namespace DirectUI
{
	namespace Shapes
	{
		class __declspec(dllexport) Ellipse : public Control::CControl
		{
		public:
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
		};
	}
}


