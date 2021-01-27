#pragma once
#include "CControl.h"
#include "CD2D_ImageSource.h"

namespace DirectUI
{
	namespace Control
	{
		//
	// 摘要:
	//     描述如何調整內容大小以填滿其配置空間。
		enum class Stretchs
		{
			//
			// 摘要:
			//     內容會保留其原始大小。
			None = 0,
			//
			// 摘要:
			//     內容會調整大小以填滿目的尺寸。 不會保留長寬比。
			Fill = 1,
			//
			// 摘要:
			//     內容會調整大小以符合目的尺寸，同時也會保留其原始長寬比。
			Uniform = 2,
			//
			// 摘要:
			//     內容會調整大小以填滿目的尺寸，同時也會保留其原始長寬比。 如果目的矩形的長寬比與來源不同，則會裁剪來源內容使其符合目的尺寸。
			UniformToFill = 3
		};
		class __declspec(dllexport) CImage:public CControl
		{
		public:
			void SetSource(shared_ptr<CD2D_ImageSource> data);
			void SetStretch(Stretchs data);
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			void Arrange(float x, float y, float width, float height) override;
		protected:
			D2D1_SIZE_F GetSize(float width, float height) override;
			D2D1_RECT_F Calculate_Uniform(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst);
			D2D1_RECT_F Calculate_UniformToFill(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst);
			D2D1_RECT_F LetterBoxRect(const D2D1_RECT_F& rcSrc, const D2D1_RECT_F& rcDst);
			void Release() override;
			ID2D1Bitmap* m_pD2DBitmap = NULL;
			shared_ptr<CD2D_ImageSource> m_Source;
			Stretchs m_Stretch = Stretchs::Uniform;
		};
	}
}

