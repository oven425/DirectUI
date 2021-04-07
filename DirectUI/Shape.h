#pragma once
#include "UIElement.h"
using namespace DirectUI;

namespace DirectUI
{
	namespace Shapes
	{
		class __declspec(dllexport) Shape : public Control::UIElement
		{
		public:
			Shape();
			__declspec(property(get = GetFill, put = SetFill)) shared_ptr<Direct2D::CD2D_Brush> Fill;
			void SetFill(shared_ptr<Direct2D::CD2D_Brush> data);
			shared_ptr<Direct2D::CD2D_Brush> GetFill();

			__declspec(property(get = GetStretch, put = SetStretch)) Control::Stretchs Stretch;
			void SetStretch(Control::Stretchs data);
			Control::Stretchs GetStretch();
			void SetStroke(shared_ptr<Direct2D::CD2D_Brush> data);
			shared_ptr<Direct2D::CD2D_Brush> GetStroke();
			__declspec(property(get = GetStroke, put = SetStroke)) shared_ptr<Direct2D::CD2D_Brush> Stroke;
			void SetStrokeThickness(float data);
			float GetStrokeThickness();
			__declspec(property(get = GetStrokeThickness, put = SetStrokeThickness)) float StrokeThickness;
		protected:
			static shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>> FillProperty;
			static shared_ptr<DependencyProperty<int>> StretchProperty;
			static shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>> StrokeProperty;
			static shared_ptr<DependencyProperty<float>> StrokeThicknessProperty;
		};
	}
}

