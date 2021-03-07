#include "pch.h"
#include "CPanel.h"
using namespace DirectUI;
using namespace Control;

bool CPanel::HitTest(int x, int y, vector<shared_ptr<CControl>>& childs)
{
	bool result = false;
	result = ::CControl::HitTest(x, y, childs);
	if (result == true)
	{
		for (auto oo : this->m_Childs)
		{
			result = oo->HitTest(x, y, childs);
			if (result == true)
			{
				break;
			}
		}
	}
	
	return result;
	//return nullptr;
}