#pragma once
class Brush
{
public:
	virtual operator ID2D1Brush* () { return NULL; }
};


class SoildColorBrush:Brush
{
public:

	D2D1::ColorF m_Color;
	operator ID2D1Brush* () override
	{
		return m_Brush;
	}
	void SetColor(D2D1::ColorF data)
	{

	}
private:
	CComPtr<ID2D1SolidColorBrush> m_Brush;

};
