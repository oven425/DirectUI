#include "pch.h"
#include "CPanel.h"
using namespace DirectUI;
using namespace Control;

shared_ptr<CControl> CPanel::HitTest(int x, int y)
{
	for (auto oo : this->m_Childs)
	{
		shared_ptr<CControl> temp = oo->HitTest(x, y);
		if (temp)
		{
			return temp;
			break;
		}
	}

	return nullptr;
}