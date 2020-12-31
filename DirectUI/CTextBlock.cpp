#include "pch.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;

void CTextBlock::OnRender(ID2D1RenderTarget* pRT)
{
	::CControl::OnRender(pRT);
	if (this->m_Text.empty() == false)
	{

	}
}