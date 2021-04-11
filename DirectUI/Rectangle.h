#pragma once
#include "Shape.h"
namespace DirectUI
{
	namespace Shapes
	{
		class __declspec(dllexport) Rectangle : public Shape
		{
		public:
			Rectangle();
			void SetRadiusX(float data);
			float GetRadiusX();
			void SetRadiusY(float data);
			float GetRadiusY();
			__declspec(property(get = GetRadiusX, put = SetRadiusX)) float RadiusX;
			__declspec(property(get = GetRadiusY, put = SetRadiusY)) float RadiusY;
		public:
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
		protected:
			static shared_ptr<DependencyProperty<float>> RadiusXProperty;
			static shared_ptr<DependencyProperty<float>> RadiusYProperty;
		};
	}
}


