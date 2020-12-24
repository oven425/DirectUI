#include "pch.h"
#include "CContentControl.h"
using namespace DirectUI;
using namespace Control;

void CContentControl::OnRender(ID2D1HwndRenderTarget* pRT)
{
	if (this->m_Child != nullptr)
	{
		this->m_Child->OnRender(pRT);
	}
	
}