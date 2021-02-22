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
		protected:
			vector<shared_ptr<CControl>> m_Childs;
		};
	}
}


