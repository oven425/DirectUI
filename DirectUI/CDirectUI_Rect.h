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
			CDirectUI_Rect(const CDirectUI_Rect& data)
			{
				this->m_Left = data.m_Left;
				this->m_Top = data.m_Top;
				this->m_Right = data.m_Right;
				this->m_Bottom = data.m_Bottom;
			}
			CDirectUI_Rect(float left, float top, float right, float bottom)
			{
				this->m_Left = left;
				this->m_Top = top;
				this->m_Right = right;
				this->m_Bottom = bottom;
			}
			void SetLeft(float data) { this->m_Left = data; }
			void SetTop(float data) { this->m_Top = data; }
			void SetRight(float data) { this->m_Right = data; }
			void SetBottom(float data) { this->m_Bottom = data; }
			void SetX(float data) { this->m_Left = data; }
			void SetY(float data) { this->m_Top = data; }
			void SetWidth(float data) { this->m_Right = this->m_Left + data; }
			void SetHeight(float data) { this->m_Bottom = this->m_Top + data; }
			float GetX() { return this->m_Left; }
			float GetY() { return this->m_Top; }
			float GetWidth() { return this->m_Right - this->m_Left; }
			float GetHeight() { return this->m_Bottom - this->m_Top; }
			float GetLeft() { return this->m_Left; }
			float GetTop() { return this->m_Top; }
			float GetRight() { return this->m_Right; }
			float GetBottom() { return this->m_Bottom; }
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

			CDirectUI_Rect operator/(float data) const throw()
			{
				CDirectUI_Rect rc;
				rc.m_Left = this->m_Left / data;
				rc.m_Right = this->m_Right / data;
				rc.m_Top = this->m_Top / data;
				rc.m_Bottom = this->m_Bottom / data;
				return rc;
			}
		protected:
			float m_Left = 0;
			float m_Top = 0;
			float m_Bottom = 0;
			float m_Right = 0;
		};
	}
}

