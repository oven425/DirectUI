#include "pch.h"
#include "CStackPanel.h"
using namespace DirectUI;
using namespace Control;
void CStackPanel::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
}

void CStackPanel::OnSize(double width, double height, double dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
}

void CStackPanel::OnRender(ID2D1HwndRenderTarget* pRT)
{
	CControl::OnRender(pRT);
	for(auto oo : this->m_Childs)
	{
		oo->OnRender(pRT);
	}
}