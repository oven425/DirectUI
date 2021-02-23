#pragma once
#include "CD2D_Brush.h"

namespace DirectUI
{
	namespace Direct2D
	{
		class __declspec(dllexport) CD2D_LinearGradientBrush :public CD2D_Brush
		{
		public:
			CD2D_LinearGradientBrush(D2D1_GRADIENT_STOP* data, int count);
			virtual ~CD2D_LinearGradientBrush();
			virtual void Refresh(ID2D1RenderTarget* target) override;
			operator ID2D1Brush*() { return this->m_pBrush; }
			void Release() override;
		protected:
			ID2D1GradientStopCollection* m_pGradientStops = NULL;
			ID2D1LinearGradientBrush* m_pBrush = NULL;
			//D2D1_GRADIENT_STOP* m_pData = NULL;
			unique_ptr<D2D1_GRADIENT_STOP[]> m_pData;
		};
	}
	
}


