#pragma once
#include "CControl.h"
#include "CD2D_ImageSource.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CImage:public CControl
		{
		public:
			CImage();
			void SetSource(shared_ptr<Direct2D::CD2D_ImageSource> data);
			void SetStretch(Stretchs data);
			Stretchs GetStretch();
			__declspec(property(get = GetStretch, put = SetStretch)) Stretchs Stretch;
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Measure(const CDirectUI_Rect& data, ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
		protected:
			D2D1_RECT_F Calculate_Uniform(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst);
			D2D1_RECT_F Calculate_UniformToFill(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst);
			void Release() override;
			ID2D1Bitmap* m_pD2DBitmap = NULL;
			shared_ptr<Direct2D::CD2D_ImageSource> m_Source;
			//Stretchs m_Stretch = Stretchs::Uniform;
			static shared_ptr<DependencyProperty<int>> StretchProperty;
			CDirectUI_Rect MappingToSource(CDirectUI_Rect& actual_rect, const CDirectUI_Size& measure_size, bool ignore_x = false, bool ignore_y=false);
		};
	}
}

