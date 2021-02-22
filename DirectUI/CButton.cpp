#include "pch.h"
#include "CButton.h"
#include "CTextBlock.h"
#include "CD2D_SolidColorBrush.h"
using namespace DirectUI;
using namespace Control;

CButton::CButton()
{
	this->m_Child = m_Template = make_shared<CBorder>();
	this->m_Template->SetBorderThickness(CDirectUI_Thinkness(1.0));
	this->m_NormalBr = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(112,112,122));
	this->m_NormalBK = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(221, 221, 221));
	this->m_Template->SetBackground(this->m_NormalBK);
	this->m_Template->BorderBrush = this->m_NormalBr;
}

void CButton::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	this->m_Template->OnRender(pRT, calculate_dpi);
}

void CButton::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	::CContentControl::Measure(width, height, pRT);
}

void CButton::Arrange(float x, float y, float width, float height)
{
	::CContentControl::Arrange(x, y, width, height);
}

void CButton::OnMouseMove(const MouseMoveArgs& args)
{
	
}

void CButton::OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args)
{

}

void CButton::SetContent(const wchar_t* data)
{
	shared_ptr<CTextBlock> textblock = ::make_shared<CTextBlock>();
	textblock->SetText(data);
	m_Template->SetChild(textblock);
}

void CButton::SetContent(shared_ptr<CControl> data)
{
	this->m_Child = data;
}