#include "pch.h"
#include "CStackPanel.h"
using namespace DirectUI;
using namespace Control;
void CStackPanel::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
}

void CStackPanel::OnSize(float width, float height, float dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
	for (auto oo : this->m_Childs)
	{
		oo->OnSize(width, height, dpiscale);
		//oo->Measure(width, height);
	}
	
	
	
}

void CStackPanel::OnRender(ID2D1HwndRenderTarget* pRT)
{
	CControl::OnRender(pRT);
	for(auto oo : this->m_Childs)
	{
		oo->OnRender(pRT);
	}
}

void CStackPanel::Measure(float width, float height)
{
	::CControl::Measure(width, height);
	for (auto oo : this->m_Childs)
	{
		oo->Measure(width, height);
	}
}

void CStackPanel::Arrange(float x, float y, float width, float height)
{
	CControl::Arrange(x, y, width, height);
	switch (this->m_Orientation)
	{
	case Orientations::Vertical:
	{
		double y = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(0, y, width, oo->DesiredSize.height);
			y = y + oo->DesiredSize.height;
		}
	}
	break;
	case Orientations::Horizontal:
	{
		double x = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(x, 0, oo->DesiredSize.width, height);
			x = x + oo->DesiredSize.width;
		}
	}
	break;
	}
}

void CStackPanel::SetOrientation(Orientations data)
{
	this->m_Orientation = data;
}