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

void CContentControl::OnRender(ID2D1RenderTarget* pRT)
{
	::CControl::OnRender(pRT);
	if (this->m_Child != nullptr)
	{
		this->m_Child->OnRender(pRT);
	}
}

void CContentControl::Arrange(float x, float y, float width, float height)
{
	CControl::Arrange(x, y, width, height);
	if (this->m_Child)
	{
		this->m_Child->Arrange(x, y, width, height);
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