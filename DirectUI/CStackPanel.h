#pragma once
#include "CControl.h"
#include <list>
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
		protected:
			void OnSize(double width, double height, double dpiscale) override;
			void OnRender(ID2D1HwndRenderTarget* pRT) override;
			list<shared_ptr<CControl>> m_Childs;
			Orientations m_Orientation = Orientations::Vertical;

		};
	}
}
