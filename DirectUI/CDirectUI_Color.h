#pragma once
#include <d2d1.h>

namespace DirectUI
{
	class CDirectUI_Color
	{
	public:
		CDirectUI_Color() {}
		CDirectUI_Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
		{
			this->m_Red = red;
			this->m_Green = green;
			this->m_Blue = blue;
			this->m_Alpha = alpha;
		}
		CDirectUI_Color(D2D1::ColorF data)
		{
			this->m_Red = (unsigned char)(data.r * 255);
			this->m_Green = (unsigned char)(data.g * 255);
			this->m_Blue = (unsigned char)(data.b * 255);
			this->m_Alpha = (unsigned char)(data.a * 255);
		}
		operator D2D1_COLOR_F() const throw()
		{
			D2D1_COLOR_F color;
			color.r = (float)(this->m_Red / 255.0);
			color.g = (float)(this->m_Green / 255.0);
			color.b = (float)(this->m_Blue / 255.0);
			color.a = (float)(this->m_Alpha / 255.0);

			return color;
		}
	protected:
		unsigned char m_Red = 0;
		unsigned char m_Green = 0;
		unsigned char m_Blue = 0;
		unsigned char m_Alpha = 255;
	};
}


