#pragma once
#include "CDirectUI_CornerRadius.h"
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
			void SetBorderThickness(const CDirectUI_Thinkness& data);
			void SetCornerRadius(CDirectUI_CornerRadius& data);
			virtual void Arrange(float x, float y, float width, float height) override;
			virtual void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			void Release() override;
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
		protected:
			ID2D1PathGeometry* BuildPath(CDirectUI_Rect rc, CDirectUI_CornerRadius corner_radius, CDirectUI_Thinkness thinkness);
			CDirectUI_CornerRadius m_CornerRadius;
			CDirectUI_Thinkness m_BorderThickness;
			ID2D1PathGeometry* m_pBorder = NULL;
		};
	}
}


