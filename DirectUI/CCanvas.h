#pragma once
#include "CPanel.h"
#include <memory>

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CCanvas:public CPanel
		{
		public:
			CCanvas();
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
			static void SetLeft(shared_ptr<CControl> element, float data);
			static float GetLeft(shared_ptr<UIElement> element);
			static void SetTop(shared_ptr<CControl> element, float data);
			static float GetTop(shared_ptr<UIElement> element);
			//static void SetRight(shared_ptr<CControl> element, float data);
			//static float GetRight(shared_ptr<CControl> element);
			//static void SetBottom(shared_ptr<CControl> element, float data);
			//static float GetBottom(shared_ptr<CControl> element);
			
		protected:
			static shared_ptr<DependencyProperty<float>> LeftProperty;
			static shared_ptr<DependencyProperty<float>> TopProperty;
			static void LeftPropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs<float>& args);
		};
	}
}


