#include "pch.h"
#include "CCanvas.h"
using namespace DirectUI;
using namespace Control;

CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Left;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Right;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Top;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Bottom;

void CCanvas::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{

}

void CCanvas::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = width;
	this->DesiredSize.height = height;
	for (auto oo : this->m_Childs)
	{
		oo->Measure(width, height, pRT);
	}
}

void CCanvas::Arrange(float x, float y, float width, float height)
{

}

void CCanvas::SetLeft(shared_ptr<CControl> control, float data)
{
	m_Left.SetValue(control, data);
}

void CCanvas::SetRight(shared_ptr<CControl> control, float data)
{
	m_Right.SetValue(control, data);
}

void CCanvas::SetTop(shared_ptr<CControl> control, float data)
{
	m_Top.SetValue(control, data);
}

void CCanvas::SetBottom(shared_ptr<CControl> control, float data)
{
	m_Bottom.SetValue(control, data);
}

void CCanvas::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
	m_Parent.SetValue(data, this->shared_from_this());
}

void CCanvas::RemoveChild(shared_ptr<CControl> data)
{
	for (auto i = this->m_Childs.begin(); i != this->m_Childs.end(); i++)
	{
		if (*i == data)
		{
			this->m_Childs.erase(i);
			break;
		}
	}
	//auto ii = m_Lefts.find(data);
	//if (ii != m_Lefts.end())
	//{
	//	m_Lefts.erase(ii);
	//}
	//ii = m_Rights.find(data);
	//if (ii != m_Rights.end())
	//{
	//	m_Rights.erase(ii);
	//}
	//ii = m_Tops.find(data);
	//if (ii != m_Tops.end())
	//{
	//	m_Tops.erase(ii);
	//}
	//ii = m_Bottoms.find(data);
	//if (ii != m_Bottoms.end())
	//{
	//	m_Bottoms.erase(ii);
	//}
}