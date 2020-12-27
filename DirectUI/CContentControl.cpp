#include "pch.h"
#include "CContentControl.h"
using namespace DirectUI;
using namespace Control;

void CContentControl::OnSize(double width, double height, double dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
	
	if (this->m_Child != nullptr)
	{
		this->m_Child->OnSize(width, height, dpiscale);
	}
}

void CContentControl::OnRender(ID2D1HwndRenderTarget* pRT)
{
	::CControl::OnRender(pRT);
	if (this->m_Child != nullptr)
	{
		this->m_Child->OnRender(pRT);
	}
	
}

void CContentControl::Arrange(double x, double y, double width, double height)
{
	CControl::Arrange(x, y, width, height);
	if (this->m_Child != nullptr)
	{
		this->m_Child->Arrange(x, y, width, height);
	}
}