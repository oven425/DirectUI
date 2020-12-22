#include "pch.h"
#include "CD2D_LinearGradientBrush.h"
using namespace DirectUI;

CD2D_LinearGradientBrush::CD2D_LinearGradientBrush(D2D1_GRADIENT_STOP* data, int count)
{
	m_pData = new D2D1_GRADIENT_STOP[count];
	::memcpy_s(this->m_pData, sizeof(D2D1_GRADIENT_STOP)*count, data, sizeof(D2D1_GRADIENT_STOP)*count);
}

CD2D_LinearGradientBrush::~CD2D_LinearGradientBrush()
{
	this->Release();
}

void CD2D_LinearGradientBrush::Refresh(ID2D1HwndRenderTarget* target)
{
	if (this->m_pBrush == NULL && target != NULL)
	{
		ID2D1GradientStopCollection *pGradientStops = NULL;
		HRESULT hr = target->CreateGradientStopCollection(
			m_pData,
			2,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			&pGradientStops
		);

		if (SUCCEEDED(hr))
		{
			hr = target->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(0, 0),
					D2D1::Point2F(150, 150)),
				pGradientStops,
				&m_pBrush
			);
		}
	}
}

void CD2D_LinearGradientBrush::Release()
{
	if (this->m_pBrush != NULL)
	{
		this->m_pBrush->Release();
		this->m_pBrush = NULL;
	}
}