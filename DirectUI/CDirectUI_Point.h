#pragma once
#include <d2d1.h>

namespace DirectUI
{
	class __declspec(dllexport) CDirectUI_Point
	{
	public:
		CDirectUI_Point(){}
		CDirectUI_Point(float x, float y) { this->m_X = x; this->m_Y = y; }
		void SetX(float data) { this->m_X = data; }
		void SetY(float data) { this->m_Y = data; }
		float GetX() { return this->m_X; }
		float GetY() { return this->m_Y; }
		operator D2D1_POINT_2F() const throw()
		{
			D2D1_POINT_2F pt = { 0 };
			pt.x = this->m_X;
			pt.y = this->m_Y;
			return pt;
		}
	protected:
		float m_X = 0;
		float m_Y = 0;
	};

}

