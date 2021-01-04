#pragma once
#include "CControl.h"
#include "CImageSource.h"

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
			void SetSource(shared_ptr<CImageSource> data);
			void SetStretch(Stretchs data);
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(float width, float height) override;
			void Arrange(float x, float y, float width, float height) override;
		protected:
			ID2D1Bitmap* m_pD2DBitmap = NULL;
			shared_ptr<CImageSource> m_Source;
			Stretchs m_Stretch = Stretchs::Uniform;
		};
	}
}

