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
			void SetBorderThickness(CDirectUI_Thinkness& data);
			void SetCornerRadius(CDirectUI_Thinkness& data);
			virtual void Arrange(float x, float y, float width, float height);
			virtual void Measure(float width, float height, ID2D1RenderTarget* pRT);
			void Release() override;
		protected:
			CDirectUI_Thinkness m_CornerRadius;
			CDirectUI_Thinkness m_BorderThickness;
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			ID2D1PathGeometry* m_pBorder = NULL;
			
		};
	}
}


