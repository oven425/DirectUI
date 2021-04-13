#pragma once
#include "Shape.h"

namespace DirectUI
{
	namespace Shapes
	{
		class __declspec(dllexport) Line : public Shape
		{
		public:
			Line();
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
		protected:
			static shared_ptr<DependencyProperty<float>> X1Property;
			static shared_ptr<DependencyProperty<float>> X2Property;
			static shared_ptr<DependencyProperty<float>> Y1Property;
			static shared_ptr<DependencyProperty<float>> Y2Property;
		};
	}
}


