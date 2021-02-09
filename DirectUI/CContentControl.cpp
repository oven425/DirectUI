#include "pch.h"
#include "CContentControl.h"
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

void CContentControl::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	::CControl::OnRender(pRT, calculate_dpi);
	if (this->m_Child != nullptr)
	{
		this->m_Child->OnRender(pRT, calculate_dpi);
	}
}

void CContentControl::Arrange(float x, float y, float width, float height)
{
	CControl::Arrange(x, y, width, height);
	if (this->m_Child)
	{
		CDirectUI_Rect rc(x, y, x + width, y + height);
		rc = rc + this->m_Padding;
		this->m_Child->Arrange(rc.GetX(), rc.GetY(), rc.GetWidth(), rc.GetHeight());
	}
}

void CContentControl::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	CControl::Measure(width, height, pRT);
	if (this->m_Child)
	{
		this->m_Child->Measure(this->DesiredSize.width, this->DesiredSize.height, pRT);
	}
}

void CContentControl::SetPadding(CDirectUI_Thinkness& data)
{
	if (this->m_Padding != data)
	{
		this->m_Padding = data;
	}
}