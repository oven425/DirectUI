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
			void SetSource(shared_ptr<Direct2D::CD2D_ImageSource> data);
			void SetStretch(Stretchs data);
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
		protected:
			D2D1_RECT_F Calculate_Uniform(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst);
			D2D1_RECT_F Calculate_UniformToFill(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst);
			void Release() override;
			ID2D1Bitmap* m_pD2DBitmap = NULL;
			shared_ptr<Direct2D::CD2D_ImageSource> m_Source;
			Stretchs m_Stretch = Stretchs::Uniform;
		};
	}
}

