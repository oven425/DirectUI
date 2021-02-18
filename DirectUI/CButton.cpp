#include "pch.h"
#include "CButton.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;

void CButton::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{

}

void CButton::Measure(float width, float height, ID2D1RenderTarget* pRT)
{

}

void CButton::Arrange(float x, float y, float width, float height)
{

}

void CButton::SetContent(const wchar_t* data)
{
	shared_ptr<CTextBlock> textblock = ::make_shared<CTextBlock>();
	textblock->SetText(data);
	this->m_Child = textblock;
}

void CButton::SetContent(shared_ptr<CControl> data)
{
	this->m_Child = data;
}