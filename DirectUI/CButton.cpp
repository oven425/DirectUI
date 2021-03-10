#include "pch.h"
#include "CButton.h"
#include "CTextBlock.h"
#include "CD2D_SolidColorBrush.h"
using namespace DirectUI;
using namespace Direct2D;
using namespace Control;

CButton::CButton()
{
	
}

void CButton::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	float w = width - this->m_Margin.GetLeft() - this->m_Margin.GetRight();
	float h = height - this->m_Margin.GetTop() - this->m_Margin.GetBottom();
	::CContentControl::Measure(w, h, pRT);
}

void CButton::Arrange(float x, float y, float width, float height)
{
	::CContentControl::Arrange(x, y, width, height);
}

void CButton::OnMouseEnter(const MouseMoveArgs& args)
{
	CContentControl::OnMouseEnter(args);
	this->m_Template->SetBackground(this->m_HoverBK);
	this->m_Template->SetBorderBrush(this->m_HoverBr);
}

void CButton::OnMouseLeave(const MouseMoveArgs& args)
{
	CContentControl::OnMouseLeave(args);
	this->m_Template->SetBackground(this->m_NormalBK);
	this->m_Template->SetBorderBrush(this->m_NormalBr);
}

void CButton::OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args)
{
	this->m_Template->SetBackground(this->m_PressBK);
	this->m_Template->SetBorderBrush(this->m_PressBr);
}

void CButton::OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args)
{
	if (this->m_IsHover == true)
	{
		this->m_Template->SetBackground(this->m_HoverBK);
		this->m_Template->SetBorderBrush(this->m_HoverBr);
	}
	else
	{
		this->m_Template->SetBackground(this->m_NormalBK);
		this->m_Template->SetBorderBrush(this->m_NormalBr);
	}
	
}

void CButton::SetContent(const wchar_t* data)
{
	//this->m_Child = this->m_Template = make_shared<CBorder>();
	if (!this->m_Template)
	{
		this->m_Template = make_shared<CBorder>();
		this->m_Template->SetTree(Trees::Visual);
		this->m_Template->SetBorderThickness(CDirectUI_Thinkness(1.0));
		this->m_NormalBr = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(217, 217, 217));
		this->m_NormalBK = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(255, 255, 255));
		this->m_HoverBr = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(112, 192, 231));
		this->m_HoverBK = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(229, 243, 251));
		this->m_PressBK = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(196, 229, 246));
		this->m_PressBr = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(44, 98, 139));

		this->m_Template->SetBackground(this->m_NormalBK);
		this->m_Template->SetBorderBrush(this->m_NormalBr);
	}
	

	shared_ptr<CTextBlock> textblock = ::make_shared<CTextBlock>();
	textblock->SetHorizontalAlignment(HorizontalAlignments::Center);
	textblock->SetVerticalAlignment(VerticalAlignments::Center);
	textblock->SetForeground(::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black)));
	textblock->SetText(data);
	m_Template->SetChild(textblock);


	this->SetChild(this->m_Template);
}

void CButton::SetContent(shared_ptr<CControl> data)
{
	this->m_Child = data;
}