#include "pch.h"
#include "CContentControl.h"
using namespace DirectUI;
using namespace Control;

void CContentControl::OnSize(int width, int height)
{
	::CControl::OnSize(width, height);
	if (this->m_Child != nullptr)
	{
		this->m_Child->OnSize(width, height);
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