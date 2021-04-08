#include "pch.h"
#include "CStackPanel.h"
using namespace DirectUI;
using namespace Control;

shared_ptr<DependencyProperty<int>> CStackPanel::OrientationProperty;


CStackPanel::CStackPanel()
{
	if (!OrientationProperty)
	{
		OrientationProperty = ::make_shared<DependencyProperty<int>>();
	}
	this->Orientation = Orientations::Vertical;
}

void CStackPanel::OnSize(float width, float height, float dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
	for (auto oo : this->m_Childs)
	{
		oo->OnSize(width, height, dpiscale);
	}
}

void CStackPanel::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);
	
	for (auto oo : this->m_Childs)
	{
		oo->OnRender(this->m_pRenderBuf);
	}

	::CControl::OnRender(pRT);
}

void CStackPanel::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Size stackpanel_sz = data + this->m_Margin;
	switch (this->Orientation)
	{
	case Orientations::Vertical:
	{
		for (auto oo : this->m_Childs)
		{
			oo->Measure(CDirectUI_Size(stackpanel_sz.GetWidth(), 0), pRT);
			this->DesiredSize.height = this->DesiredSize.height + oo->DesiredSize.height;
		}
		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<UIElement> c1, shared_ptr<UIElement> c2) {return c1->DesiredSize.width > c2->DesiredSize.width; });
		this->DesiredSize.width = (*aaa)->DesiredSize.width;
	}
	break;
	case Orientations::Horizontal:
	{
		this->DesiredSize.height = stackpanel_sz.GetHeight();
		for (auto oo : this->m_Childs)
		{
			oo->Measure(CDirectUI_Size(0, stackpanel_sz.GetHeight()), pRT);
			this->DesiredSize.width = this->DesiredSize.width + oo->DesiredSize.width;
		}

		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<UIElement> c1, shared_ptr<UIElement> c2) {return c1->DesiredSize.height > c2->DesiredSize.height; });
		this->DesiredSize.height = (*aaa)->DesiredSize.height;
	}
	break;
	}

	if (this->m_Width > 0 && this->m_Width < this->DesiredSize.width)
	{
		this->DesiredSize.width = this->m_Width;
	}
	else if (this->DesiredSize.width < stackpanel_sz.GetWidth())
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = stackpanel_sz.GetWidth();
		}
	}
	if (this->m_Height > 0 && this->m_Height < this->DesiredSize.height)
	{
		this->DesiredSize.height = this->m_Height;
	}
	else if (this->DesiredSize.height < stackpanel_sz.GetHeight())
	{
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = stackpanel_sz.GetHeight();
		}
	}
}

void CStackPanel::Arrange(const CDirectUI_Rect& data)
{
	CDirectUI_Rect rc = data + this->m_Margin;
	float w = this->DesiredSize.width;
	float h = this->DesiredSize.height;
	if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
	{
		if (w > rc.GetWidth() - this->m_Margin.GetLeft() - this->m_Margin.GetRight())
		{
			w = rc.GetWidth();
		}
	}
	if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
	{
		if (h > rc.GetHeight() - this->m_Margin.GetTop() - this->m_Margin.GetBottom())
		{
			h = rc.GetHeight();
		}
	}
	switch (this->Orientation)
	{
	case Orientations::Vertical:
	{
		float y = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(CDirectUI_Rect(0, y, w, y+oo->DesiredSize.height));
			y = y + oo->GetActualRect().GetHeight();
		}
	}
	break;
	case Orientations::Horizontal:
	{
		float x = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(CDirectUI_Rect(x, 0, x+oo->DesiredSize.width, h));
			x = x + oo->GetActualRect().GetWidth();
		}
	}
	break;
	}

	CControl::Arrange(data);
}

void CStackPanel::SetOrientation(Orientations data)
{
	this->SetValue(OrientationProperty, (int)data);
}

Orientations CStackPanel::GetOrientation() 
{ 
	return (Orientations)this->GetValue<int>(OrientationProperty);
}