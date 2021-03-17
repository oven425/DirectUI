#include "pch.h"
#include "CButton.h"
#include "CTextBlock.h"
#include "CD2D_SolidColorBrush.h"
using namespace DirectUI;
using namespace Direct2D;
using namespace Control;

bool CButton::HitTest(int x, int y, vector<shared_ptr<CControl>>& childs)
{
	return ::CContentControl::HitTest(x, y, childs);
}

void CButton::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	::CContentControl::Measure(data, pRT);
}

void CButton::Arrange(const CDirectUI_Rect& data)
{
	::CContentControl::Arrange(data);
}

void CButton::OnMouseEnter(const MouseMoveArgs& args)
{
	CContentControl::OnMouseEnter(args);
	
	if (this->m_IsPressed == true)
	{
		this->m_Template->SetBackground(this->m_PressBK);
		this->m_Template->SetBorderBrush(this->m_PressBr);
	}
	else
	{
		this->m_Template->SetBackground(this->m_HoverBK);
		this->m_Template->SetBorderBrush(this->m_HoverBr);
	}
}

void CButton::OnMouseLeave(const MouseMoveArgs& args)
{
	CContentControl::OnMouseLeave(args);
	if (this->m_IsPressed == true)
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

void CButton::OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args)
{
	CContentControl::OnMouseLeftButtonDown(args);
	this->m_IsCaptureMouse = true;
	this->m_Template->SetBackground(this->m_PressBK);
	this->m_Template->SetBorderBrush(this->m_PressBr);
}

void CButton::OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args)
{
	CContentControl::OnMouseLeftButtonUp(args);
	this->m_IsCaptureMouse = false;
	if (this->m_IsMouseOver == true)
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
	if (!this->m_Template)
	{
		this->m_Template = make_shared<CBorder>();
		this->m_Template->Name = L"button_border";
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
	textblock->Name = L"button_border_textblock";
	m_Template->SetChild(textblock);


	this->SetChild(this->m_Template);
}

void CButton::SetContent(shared_ptr<CControl> data)
{
	this->m_Child = data;
}