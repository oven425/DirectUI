#pragma once
#include <vector>
#include <map>
using namespace std;

#include "CPanel.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CCanvas : public CPanel
		{
		public:
			void AddChild(shared_ptr<CControl> data);
			void RemoveChild(shared_ptr<CControl> data);
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			void Arrange(float x, float y, float width, float height) override;
			static void SetLeft(shared_ptr<CControl> control, float data);
			static void SetRight(shared_ptr<CControl> control, float data);
			static void SetTop(shared_ptr<CControl> control, float data);
			static void SetBottom(shared_ptr<CControl> control, float data);
		protected:
			static CDependencyObject<shared_ptr<CControl>, float> m_Left;
			static CDependencyObject<shared_ptr<CControl>, float> m_Right;
			static CDependencyObject<shared_ptr<CControl>, float> m_Top;
			static CDependencyObject<shared_ptr<CControl>, float> m_Bottom;
		};
	}
}


