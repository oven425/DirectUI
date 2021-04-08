#pragma once
#include "CPanel.h"
#include <vector>
using namespace std;

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CStackPanel :public CPanel
		{
		public:
			CStackPanel();
			void SetOrientation(Orientations data);
			Orientations GetOrientation();
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
			__declspec(property(get = GetOrientation, put = SetOrientation)) Orientations Orientation;
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
			//Orientations m_Orientation = Orientations::Vertical;
			static shared_ptr<DependencyProperty<int>> OrientationProperty;
		};
	}
}

