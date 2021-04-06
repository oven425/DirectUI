#pragma once
#include "Shape.h"
using namespace DirectUI;
using namespace Control;

namespace DirectUI
{
	namespace Shapes
	{
		class __declspec(dllexport) Ellipse : public Shape
		{
		public:
			Ellipse();
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
			void SetStroke(shared_ptr<Direct2D::CD2D_Brush> data);
			shared_ptr<Direct2D::CD2D_Brush> GetStroke();
			__declspec(property(get = GetStroke, put = SetStroke)) shared_ptr<Direct2D::CD2D_Brush> Stroke;
			void SetStrokeThickness(float data);
			float GetStrokeThickness();
			__declspec(property(get = GetStrokeThickness, put = SetStrokeThickness)) float StrokeThickness;
		protected:
			static shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>> StrokeProperty;
			static void StrokePropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs<Direct2D::CD2D_Brush>& args);
			static shared_ptr<DependencyProperty<float>> StrokeThicknessProperty;
			
		};
	}
}


