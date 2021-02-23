#pragma once
#include "CD2D_Brush.h"

namespace DirectUI
{
	namespace Direct2D
	{
		class __declspec(dllexport) CD2D_SolidColorBrush : public CD2D_Brush
		{
		public:
			CD2D_SolidColorBrush(const CDirectUI_Color& color);
			virtual ~CD2D_SolidColorBrush();
			virtual void Refresh(ID2D1RenderTarget* target) override;
			operator ID2D1Brush*() { return this->m_pBrush; }
			void Release() override;
		protected:

			ID2D1SolidColorBrush* m_pBrush = NULL;
			CDirectUI_Color m_Color;
			//D2D1_COLOR_F m_Color;
		};
	}
	
}

