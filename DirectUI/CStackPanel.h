#pragma once
#include "CControl.h"
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
		class __declspec(dllexport) CStackPanel :public CControl
		{
		public:
			void AddChild(shared_ptr<CControl> data);
			void SetOrientation(Orientations data);
			Orientations GetOrientation() { return this->m_Orientation; };
			virtual void Measure(float width, float height, ID2D1RenderTarget* pRT) override;
			virtual void Arrange(float x, float y, float width, float height) override;
		protected:
			void OnSize(float width, float height, float dpiscale) override;
			void OnRender(ID2D1RenderTarget* pRT) override;
			vector<shared_ptr<CControl>> m_Childs;
			Orientations m_Orientation = Orientations::Vertical;

		};
	}
}

