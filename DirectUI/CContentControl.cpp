#include "pch.h"
#include "CContentControl.h"
#include <typeinfo>
using namespace DirectUI;
using namespace Control;

shared_ptr<DependencyProperty<shared_ptr<CDirectUI_Thinkness>>> CContentControl::PaddingProperty;

CContentControl::CContentControl()
{
	if (!PaddingProperty)
	{
		PaddingProperty = ::make_shared<DependencyProperty<shared_ptr<CDirectUI_Thinkness>>>();
		PaddingProperty->m_Default = ::make_shared<CDirectUI_Thinkness>();
	}
}

void CContentControl::OnSize(float width, float height, float dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
	
	if (this->m_Child != nullptr)
	{
		this->m_Child->OnSize(width, height, dpiscale);
	}
}

void CContentControl::OnRender(ID2D1RenderTarget* pRT)
{
	
	//this->CreateRenderBuf(pRT, this->DesiredSize);
	//if (this->m_Child != nullptr)
	//{
	//	this->m_Child->OnRender(this->m_pRenderBuf);
	//}
	//::CControl::OnRender(pRT);
	::CControl::OnRender(pRT);
	if (this->m_Child)
	{
		this->m_Child->OnRender(pRT);
	}
	
}

void CContentControl::Arrange(const CDirectUI_Rect& data)
{
	if (this->m_Child)
	{
		CControl::Arrange(data);

		CDirectUI_Rect rc = this->m_ActualRect;


		rc = this->DesiredSize;
		if (this->Padding)
		{
			rc = rc + *this->Padding;
		}
		

		this->m_Child->Arrange(rc);
	}
	else
	{
		CControl::Arrange(data);
	}
}

void CContentControl::Measure(const CDirectUI_Rect& data, ID2D1RenderTarget* pRT)
{
	this->m_MeasureRect = 0;
	
	if (this->m_Child)
	{
		CDirectUI_Rect rc = data + *this->Margin+*this->Padding;
		this->m_Child->Measure(rc, pRT);
		this->m_MeasureRect = this->m_Child->m_MeasureRect + *this->Margin + *this->Padding;
		switch (this->m_HorizontalAlignment)
		{
		case HorizontalAlignments::Stretch:
		{
			this->m_MeasureRect.SetX(data.GetLeft());
			this->m_MeasureRect.SetWidth(data.GetWidth());
		}
		break;
		}
		switch (this->m_VerticalAlignment)
		{
		case VerticalAlignments::Stretch:
		{
			this->m_MeasureRect.SetY(data.GetTop());
			this->m_MeasureRect.SetHeight(data.GetHeight());
		}
		break;
		}
	}
	else
	{
		CControl::Measure(data, pRT);
	}
}

void CContentControl::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Size border_sz = data + *this->Margin;
	if (this->m_Child)
	{
		CDirectUI_Size child_sz = border_sz;
		if (this->Padding)
		{
			border_sz + *this->Padding;
		}
		this->m_Child->Measure(child_sz, pRT);
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = border_sz.GetWidth();
		}
		else
		{
			this->DesiredSize.width = this->m_Child->DesiredSize.width;
		}
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = border_sz.GetHeight();
		}
		else
		{
			this->DesiredSize.height = this->m_Child->DesiredSize.height;
		}

	}
	else
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = border_sz.GetWidth();
		}
		else
		{
			//this->DesiredSize.width = this->m_BorderThickness.GetLeft() + this->m_BorderThickness.GetRight();
		}
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = border_sz.GetHeight();
		}
		else
		{
			//this->DesiredSize.height = this->m_BorderThickness.GetTop() + this->m_BorderThickness.GetBottom();
		}

	}
}

void CContentControl::SetPadding(shared_ptr<CDirectUI_Thinkness> data)
{
	//this->SetValue(PaddingProperty, data);
}

shared_ptr<CDirectUI_Thinkness> CContentControl::GetPadding()
{
	return this->GetValue<shared_ptr<CDirectUI_Thinkness>>(PaddingProperty);
	//return  static_pointer_cast<CDirectUI_Thinkness>(obj);
	return nullptr;
}

void CContentControl::SetChild(shared_ptr<UIElement> data)
{
	this->m_Child = data;
	this->SetRoot(this->m_Root);
}

bool CContentControl::HitTest(int x, int y, vector<shared_ptr<UIElement>>& childs)
{
	bool result = false;

	result = CControl::HitTest(x, y, childs);
	

	if (result == true && this->m_Child && this->m_Child->GetTree()==Trees::Logic)
	{
		this->m_Child->HitTest(x, y, childs);
	}
	return result;
}

void CContentControl::SetRoot(weak_ptr<UIElement> data)
{
	this->m_Root = data;
	if (this->m_Child)
	{
		this->m_Child->SetRoot(data);
	}
}