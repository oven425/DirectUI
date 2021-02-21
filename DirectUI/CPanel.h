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
			shared_ptr<CControl> HitTest(int x, int y) override;
		protected:
			vector<shared_ptr<CControl>> m_Childs;
		};
	}
}


