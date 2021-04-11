#pragma once
#include "CDirectUI_Rect.h"

namespace DirectUI
{
	class  __declspec(dllexport) CDirectUI_RoundedRect
	{
	public:
		CDirectUI_RoundedRect(CDirectUI_Rect data, float radius_x, float radius_y)
		{
			this->m_Rect = data;
			this->m_RadiusX = radius_x;
			this->m_RadiusY = radius_y;
		}
		operator D2D1_ROUNDED_RECT() const throw()
		{
			D2D1_ROUNDED_RECT rc;
			rc.rect = this->m_Rect;
			rc.radiusX = this->m_RadiusX;
			rc.radiusY = this->m_RadiusY;
			return rc;
		}
	protected:
		CDirectUI_Rect m_Rect;
		float m_RadiusX = 0;
		float m_RadiusY = 0;
	};
}


