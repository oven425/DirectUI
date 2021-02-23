#include "pch.h"
#include "CD2D_LinearGradientBrush.h"
using namespace DirectUI;
using namespace Direct2D;

CD2D_LinearGradientBrush::CD2D_LinearGradientBrush(D2D1_GRADIENT_STOP* data, int count)
{
	//m_pData = new D2D1_GRADIENT_STOP[count];
	//::memcpy_s(this->m_pData, sizeof(D2D1_GRADIENT_STOP)*count, data, sizeof(D2D1_GRADIENT_STOP)*count);
	this->m_pData = ::make_unique<D2D1_GRADIENT_STOP[]>(count);
	::memcpy_s(&this->m_pData[0], sizeof(D2D1_GRADIENT_STOP)*count, data, sizeof(D2D1_GRADIENT_STOP)*count);
}

CD2D_LinearGradientBrush::~CD2D_LinearGradientBrush()
{
	this->Release();
}

void CD2D_LinearGradientBrush::Refresh(ID2D1RenderTarget* target)
{
	if (this->m_pBrush == NULL && target != NULL)
	{
		HRESULT hr = target->CreateGradientStopCollection(
			&this->m_pData[0],
			2,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			&this->m_pGradientStops
		);

		if (SUCCEEDED(hr))
		{
			hr = target->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(0, 0),
					D2D1::Point2F(150, 150)),
				this->m_pGradientStops,
				&m_pBrush
			);
		}
	}
}

void CD2D_LinearGradientBrush::Release()
{
	if (this->m_pGradientStops != NULL)
	{
		this->m_pGradientStops->Release();
		this->m_pGradientStops = NULL;
	}
	if (this->m_pBrush != NULL)
	{
		this->m_pBrush->Release();
		this->m_pBrush = NULL;
	}
}