#pragma once
#include <d2d1.h>
#include "CDirectUI_Thinkness.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CDirectUI_Rect
		{
		public:
			CDirectUI_Rect() {}
			CDirectUI_Rect(double left, double top, double right, double bottom)
			{
				this->m_Left = left;
				this->m_Top = top;
				this->m_Right = right;
				this->m_Bottom = bottom;
			}
			void SetLeft(double data) { this->m_Left = data; }
			void SetTop(double data) { this->m_Top = data; }
			void SetRight(double data) { this->m_Right = data; }
			void SetBottom(double data) { this->m_Bottom = data; }
			void SetX(double data) { this->m_Left = data; }
			void SetY(double data) { this->m_Top = data; }
			void SetWidth(double data) { this->m_Right = this->m_Left + data; }
			void SetHeight(double data) { this->m_Bottom = this->m_Top + data; }
			double GetX() { return this->m_Left; }
			double GetY() { return this->m_Top; }
			double GetWidth() { return this->m_Right - this->m_Left; }
			double GetHeight() { return this->m_Bottom - this->m_Top; }
			double GetLeft() { return this->m_Left; }
			double GetTop() { return this->m_Top; }
			double GetRight() { return this->m_Right; }
			double GetBottom() { return this->m_Bottom; }
			operator D2D1_RECT_F() const throw()
			{
				D2D1_RECT_F rc;
				rc.bottom = this->m_Bottom;
				rc.right = this->m_Right;
				rc.left = this->m_Left;
				rc.top = this->m_Top;
				return rc;
			}
			
			CDirectUI_Rect operator+(CDirectUI_Thinkness& data) const throw()
			{
				CDirectUI_Rect rc;
				rc.m_Bottom = this->m_Bottom - data.GetBottom();
				rc.m_Right = this->m_Right - data.GetRight();
				rc.m_Left = this->m_Left + data.GetLeft();
				rc.m_Top = this->m_Top + data.GetTop();
				return rc;
			}

			CDirectUI_Rect& operator/(double data) const throw()
			{
				CDirectUI_Rect rc;
				rc.m_Left = this->m_Left / data;
				rc.m_Right = this->m_Right / data;
				rc.m_Top = this->m_Top / data;
				rc.m_Bottom = this->m_Bottom / data;
				return rc;
			}
		protected:
			double m_Left = 0;
			double m_Top = 0;
			double m_Bottom = 0;
			double m_Right = 0;
		};
	}
}

