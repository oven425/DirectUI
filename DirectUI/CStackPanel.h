#pragma once
#include "CPanel.h"
#include <vector>
using namespace std;

namespace DirectUI
{
	namespace Control
	{
		enum class Orientations
		{
			Horizontal,
			Vertical
		};
		class __declspec(dllexport) CStackPanel :public CPanel
		{
		public:
			void AddChild(shared_ptr<CControl> data);
			void SetOrientation(Orientations data);
			Orientations GetOrientation() { return this->m_Orientation; };
			virtual void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			virtual void Arrange(float x, float y, float width, float height) override;
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			Orientations m_Orientation = Orientations::Vertical;

		};
	}
}

