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
			void AddChild(shared_ptr<CControl> data);
			void SetOrientation(Orientations data);
			Orientations GetOrientation() { return this->m_Orientation; };
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			//virtual void Arrange(float x, float y, float width, float height) override;
			virtual void Arrange(const CDirectUI_Rect& data) override;
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
			Orientations m_Orientation = Orientations::Vertical;

		};
	}
}

