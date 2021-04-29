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
			CBorder();
			void SetBorderBrush(shared_ptr<Direct2D::CD2D_Brush> data);
			shared_ptr<Direct2D::CD2D_Brush> GetBorderBrush();
			__declspec(property(get = GetBorderBrush, put = SetBorderBrush)) shared_ptr<Direct2D::CD2D_Brush> BorderBrush;
			void SetBorderThickness(const CDirectUI_Thinkness& data);
			void SetCornerRadius(CDirectUI_CornerRadius& data);
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			virtual void Measure(const CDirectUI_Rect& data, ID2D1RenderTarget* pRT) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
			void Release() override;
			void OnRender(ID2D1RenderTarget* pRT) override;
		protected:
			static shared_ptr<DependencyProperty<shared_ptr<Direct2D::CD2D_Brush>>> BorderBrushProperty;
			ID2D1PathGeometry* BuildPath(CDirectUI_Rect rc, CDirectUI_CornerRadius corner_radius, CDirectUI_Thinkness thinkness);
			CDirectUI_CornerRadius m_CornerRadius;
			CDirectUI_Thinkness m_BorderThickness;
			ID2D1PathGeometry* m_pBorder = NULL;
		};
	}
}


