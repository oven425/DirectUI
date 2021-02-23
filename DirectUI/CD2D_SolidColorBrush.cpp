#include "pch.h"
#include "CD2D_SolidColorBrush.h"
using namespace DirectUI;
using namespace Direct2D;

CD2D_SolidColorBrush::CD2D_SolidColorBrush(const CDirectUI_Color& color)
{
	this->m_Color = color;
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
	HRESULT hr = S_OK;
	if (this->m_pBrush == NULL)
	{
		hr = target->CreateSolidColorBrush(this->m_Color, &this->m_pBrush);
	}
}


