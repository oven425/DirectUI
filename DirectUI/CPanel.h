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
			bool HitTest(int x, int y, vector<shared_ptr<CControl>>& childs) override;
			void AddChild(shared_ptr<CControl> data);
			void SetRoot(weak_ptr<CControl> data) override;
		protected:
			vector<shared_ptr<CControl>> m_Childs;
			void OnSize(float width, float height, float dpiscale) override;
		};
	}
}


