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
}

void CPanel::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
	data->SetRoot(this->m_Root);
}

void CPanel::SetRoot(weak_ptr<CControl> data)
{
	this->m_Root = data;
	for (auto oo : this->m_Childs)
	{
		oo->SetRoot(data);
	}
}