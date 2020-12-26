#pragma once
#include "CControl.h"
#include <list>
using namespace std;

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CStackPanel :public CControl
		{
		public:
			void AddChild(shared_ptr<CControl> data);
		protected:
			void OnSize(double width, double height, double dpiscale) override;
			void OnRender(ID2D1HwndRenderTarget* pRT) override;
			list<shared_ptr<CControl>> m_Childs;

		};
	}
}

