#pragma once
#include "CControl.h"
#include "CD2D_ImageSource.h"

namespace DirectUI
{
	namespace Control
	{
		//
	// �K�n:
	//     �y�z�p��վ㤺�e�j�p�H�񺡨�t�m�Ŷ��C
		enum class Stretchs
		{
			//
			// �K�n:
			//     ���e�|�O�d���l�j�p�C
			None = 0,
			//
			// �K�n:
			//     ���e�|�վ�j�p�H�񺡥ت��ؤo�C ���|�O�d���e��C
			Fill = 1,
			//
			// �K�n:
			//     ���e�|�վ�j�p�H�ŦX�ت��ؤo�A�P�ɤ]�|�O�d���l���e��C
			Uniform = 2,
			//
			// �K�n:
			//     ���e�|�վ�j�p�H�񺡥ت��ؤo�A�P�ɤ]�|�O�d���l���e��C �p�G�ت��x�Ϊ����e��P�ӷ����P�A�h�|���Ũӷ����e�Ϩ�ŦX�ت��ؤo�C
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

