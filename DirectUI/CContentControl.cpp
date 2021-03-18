#include "pch.h"
#include "CContentControl.h"
#include <typeinfo>
using namespace DirectUI;
using namespace Control;

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
	this->CreateRenderBuf(pRT, this->DesiredSize);
	if (this->m_Child != nullptr)
	{
		this->m_Child->OnRender(this->m_pRenderBuf);
	}
	::CControl::OnRender(pRT);
}

void CContentControl::Arrange(const CDirectUI_Rect& data)
{
	if (this->m_Child)
	{
		CControl::Arrange(data);

		CDirectUI_Rect rc = this->m_ActualRect;
		//if (this->DesiredSize.width < rc.GetWidth())
		//{
		//	if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		//	{
		//		this->DesiredSize.width = rc.GetWidth();
		//	}
		//}
		//if (this->DesiredSize.height < rc.GetHeight())
		//{
		//	if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		//	{
		//		this->DesiredSize.height = rc.GetHeight();
		//	}
		//}

		rc = this->DesiredSize;
		rc = rc + this->m_Padding;

		this->m_Child->Arrange(rc);
	}
	else
	{
		CControl::Arrange(data);
	}
}

//void CContentControl::Arrange(float x, float y, float width, float height)
//{
//	if (this->m_Child)
//	{
//		CControl::Arrange(x, y, width, height);
//		CDirectUI_Rect rc = this->m_ActualRect;
//
//		//rc = CDirectUI_Rect(0, 0, rc.GetWidth(), rc.GetHeight());
//		rc = this->DesiredSize;
//		rc = rc + this->m_Padding;
//
//		this->m_Child->Arrange(rc.GetX(), rc.GetY(), rc.GetWidth(), rc.GetHeight());
//
//
//
//	}
//	else
//	{
//		CControl::Arrange(x, y, width, height);
//	}
//}

//void CContentControl::Measure(float width, float height, ID2D1RenderTarget* pRT)
//{
//	CControl::Measure(width, height, pRT);
//	if (this->m_Child)
//	{
//		float w = this->DesiredSize.width - this->m_Padding.GetLeft() - this->m_Padding.GetRight();
//		float h = this->DesiredSize.height - this->m_Padding.GetTop() - this->m_Padding.GetBottom();
//		this->m_Child->Measure(w, h, pRT);
//	}
//}

void CContentControl::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Size border_sz = data + this->m_Margin;
	if (this->m_Child)
	{
		CDirectUI_Size child_sz = border_sz + this->m_Padding;
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
	//CControl::Measure(data, pRT);
	//if (this->m_Child)
	//{
	//	CDirectUI_Size sz = data + this->m_Padding;
	//	//float w = this->DesiredSize.width - this->m_Padding.GetLeft() - this->m_Padding.GetRight();
	//	//float h = this->DesiredSize.height - this->m_Padding.GetTop() - this->m_Padding.GetBottom();
	//	this->m_Child->Measure(sz, pRT);
	//}
}

void CContentControl::SetPadding(CDirectUI_Thinkness& data)
{
	if (this->m_Padding != data)
	{
		this->m_Padding = data;
	}
}

void CContentControl::SetChild(shared_ptr<CControl> data)
{
	this->m_Child = data;
	//m_Parent.SetValue(data, this->shared_from_this());
}

bool CContentControl::HitTest(int x, int y, vector<shared_ptr<CControl>>& childs)
{
	bool result = false;
	//auto parent = this->m_Parent.GetValue(this->shared_from_this());

	result = CControl::HitTest(x, y, childs);
	

	if (result == true && this->m_Child && this->m_Child->GetTree()==Trees::Logic)
	{
		this->m_Child->HitTest(x, y, childs);
	}
	return result;
}