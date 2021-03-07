#include "pch.h"
#include "CButton.h"
#include "CTextBlock.h"
#include "CD2D_SolidColorBrush.h"
using namespace DirectUI;
using namespace Direct2D;
using namespace Control;

CButton::CButton()
{
	this->m_Child = m_Template = make_shared<CBorder>();
	this->m_Template->SetBorderThickness(CDirectUI_Thinkness(1.0));
	this->m_NormalBr = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(217,217,217));
	this->m_NormalBK = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(255, 255, 255));
	this->m_HoverBr = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(112, 192, 231));
	this->m_HoverBK = ::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(229, 243, 251));

	this->m_Template->SetBackground(this->m_NormalBK);
	this->m_Template->SetBorderBrush(this->m_NormalBr);
}

void CButton::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	//this->m_Template->OnRender(pRT, calculate_dpi);
	::CContentControl::OnRender(pRT, calculate_dpi);
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

void CButton::OnMouseMove(const MouseMoveArgs& args)
{
	this->m_Template->SetBackground(this->m_HoverBK);
	this->m_Template->SetBorderBrush(this->m_HoverBr);
}

void CButton::OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args)
{

}

void CButton::OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args)
{

}

void CButton::SetContent(const wchar_t* data)
{
	shared_ptr<CTextBlock> textblock = ::make_shared<CTextBlock>();
	textblock->SetHorizontalAlignment(HorizontalAlignments::Center);
	textblock->SetVerticalAlignment(VerticalAlignments::Center);
	textblock->SetForeground(::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black)));
	textblock->SetText(data);
	m_Template->SetChild(textblock);
}

void CButton::SetContent(shared_ptr<CControl> data)
{
	this->m_Child = data;
}