#include "pch.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;

void CTextBlock::OnRender(ID2D1RenderTarget* pRT)
{

}

void CTextBlock::Measure(float width, float height, ID2D1RenderTarget* pRT)
{

}

void CTextBlock::Arrange(float x, float y, float width, float height)
{

}

void CTextBlock::SetText(const wchar_t* data)
{
	this->m_Text = data;
}