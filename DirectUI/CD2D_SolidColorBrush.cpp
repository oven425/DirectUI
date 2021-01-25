#include "pch.h"
#include "CD2D_SolidColorBrush.h"
using namespace DirectUI;

CD2D_SolidColorBrush::CD2D_SolidColorBrush(const D2D1_COLOR_F& color)
{
	::memcpy_s(&this->m_Color, sizeof(D2D1_COLOR_F), &color, sizeof(D2D1_COLOR_F)); 
}

CD2D_SolidColorBrush::~CD2D_SolidColorBrush()
{
	this->Release();
}

void CD2D_SolidColorBrush::Release()
{
	if (this->m_pBrush != NULL)
	{
		this->m_pBrush->Release();
		this->m_pBrush = NULL;
	}
}

void CD2D_SolidColorBrush::Refresh(ID2D1RenderTarget* target)
{
	if (this->m_pBrush == NULL)
	{
		target->CreateSolidColorBrush(this->m_Color, &this->m_pBrush);
	}
}


