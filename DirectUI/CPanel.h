#pragma once
#include <vector>
using namespace std;
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CPanel : public CControl
		{
		public:
			bool HitTest(int x, int y, vector<shared_ptr<UIElement>>& childs) override;
			void AddChild(shared_ptr<UIElement> data);
			void SetRoot(weak_ptr<UIElement> data) override;
		protected:
			vector<shared_ptr<UIElement>> m_Childs;
			void OnSize(float width, float height, float dpiscale) override;
		};
	}
}


