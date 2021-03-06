#include "pch.h"
#include "CPanel.h"
using namespace DirectUI;
using namespace Control;

bool CPanel::HitTest(int x, int y, vector<shared_ptr<UIElement>>& childs)
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

void CPanel::OnSize(float width, float height, float dpiscale)
{
	for (auto oo : this->m_Childs)
	{
		oo->OnSize(width, height, dpiscale);
	}
}

void CPanel::AddChild(shared_ptr<UIElement> data)
{
	this->m_Childs.push_back(data);
	data->SetRoot(this->m_Root);
}

void CPanel::SetRoot(weak_ptr<UIElement> data)
{
	this->m_Root = data;
	for (auto oo : this->m_Childs)
	{
		oo->SetRoot(data);
	}
}