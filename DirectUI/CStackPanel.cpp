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

	for (auto oo : this->m_Childs)
	{
		oo->OnSize(width, height, dpiscale);
		oo->Measure(width, height);
	}
	switch (this->m_Orientation)
	{
	case Orientations::Vertical:
	{
		double y = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(0, y, width, oo->DesiredSize.cy);
			y = y + oo->DesiredSize.cy;
		}
	}
	break;
	case Orientations::Horizontal:
	{
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(0, 0, width, height);
		}
	}
	break;
	}
	
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

void CStackPanel::SetOrientation(Orientations data)
{
	this->m_Orientation = data;
}