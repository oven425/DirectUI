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
			void AddChild(shared_ptr<CControl> data);
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
			static void SetLeft(shared_ptr<CControl> element, float data);
			static float GetLeft(shared_ptr<CControl> element);
			static void SetTop(shared_ptr<CControl> element, float data);
			static float GetTop(shared_ptr<CControl> element);
			//static void SetRight(shared_ptr<CControl> element, float data);
			//static float GetRight(shared_ptr<CControl> element);
			//static void SetBottom(shared_ptr<CControl> element, float data);
			//static float GetBottom(shared_ptr<CControl> element);
			static shared_ptr<DependencyProperty> LeftProperty;
			static shared_ptr<DependencyProperty> TopProperty;
		protected:
			static void LeftPropertyChange(const DependencyObject& sender);
			
			//static CDependencyObject<shared_ptr<CControl>, float> m_Left;
			//static CDependencyObject<shared_ptr<CControl>, float> m_Top;
			//static CDependencyObject<shared_ptr<CControl>, float> m_Right;
			//static CDependencyObject<shared_ptr<CControl>, float> m_Bottom;
		};
	}
}


