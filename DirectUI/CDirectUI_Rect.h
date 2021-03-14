#pragma once
#include <iostream>
#include <sstream>
using namespace std;
#include <d2d1.h>
#include "CDirectUI_Size.h"
#include "CDirectUI_Point.h"
#include "CDirectUI_Thinkness.h"

namespace DirectUI
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
		CDirectUI_Rect(const D2D1_SIZE_F& data)
		{
			this->m_Left = 0;
			this->m_Top = 0;
			this->m_Right = data.width;
			this->m_Bottom = data.height;
		}
		CDirectUI_Rect(const CDirectUI_Size& data)
		{
			this->m_Left = 0;
			this->m_Top = 0;
			this->m_Right = data.GetWidth();
			this->m_Bottom = data.GetHeight();
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
		void SetX(float data) { this->m_Right = data + this->m_Right - this->m_Left; this->m_Left = data; }
		void SetY(float data) { this->m_Bottom = data + this->m_Bottom - this->m_Top; this->m_Top = data; }
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

		CDirectUI_Rect SetXY(float x, float y)
		{
			CDirectUI_Rect rc(this->m_Left, this->m_Top, this->m_Right, this->m_Bottom);
			rc.SetX(x);
			rc.SetY(y);
			return rc;
		}
		operator D2D1_SIZE_F() const throw()
		{
			D2D1_SIZE_F sz;
			sz.width = this->m_Right - this->m_Left;
			sz.height = this->m_Bottom - this->m_Top;
			return sz;
		}
		operator D2D1_POINT_2F() const throw()
		{
			D2D1_POINT_2F pt = { 0 };
			pt.x = this->m_Left;
			pt.y = this->m_Top;
			return pt;
		}
		operator D2D1_RECT_F() const throw()
		{
			D2D1_RECT_F rc;
			rc.bottom = this->m_Bottom;
			rc.right = this->m_Right;
			rc.left = this->m_Left;
			rc.top = this->m_Top;
			return rc;
		}

		CDirectUI_Rect operator+(CDirectUI_Thinkness data) const throw()
		{
			CDirectUI_Rect rc;
			rc.m_Bottom = this->m_Bottom - data.GetBottom();
			rc.m_Right = this->m_Right - data.GetRight();
			rc.m_Left = this->m_Left + data.GetLeft();
			rc.m_Top = this->m_Top + data.GetTop();
			return rc;
		}

		CDirectUI_Rect operator-(CDirectUI_Thinkness data) const throw()
		{
			CDirectUI_Rect rc;
			rc.m_Bottom = this->m_Bottom + data.GetBottom();
			rc.m_Right = this->m_Right + data.GetRight();
			rc.m_Left = this->m_Left - data.GetLeft();
			rc.m_Top = this->m_Top - data.GetTop();
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

		CDirectUI_Rect operator=(float data) const throw()
		{
			return CDirectUI_Rect(data, data, data, data);
		}

		bool PtInRect(float x, float y)
		{
			bool result = false;
			if (x >= this->m_Left&&x <= this->m_Right&&y >= this->m_Top&&y <= this->m_Bottom)
			{
				result = true;
			}
			return result;
		}

		virtual wstring ToString()
		{
			std::wostringstream out;
			out << "left:" << this->m_Left << " ";
			out << "top:" << this->m_Top << " ";
			out << "right:" << this->m_Right << " ";
			out << "bottom:" << this->m_Bottom << " ";
			out << "width:" << this->m_Right-this->m_Left << " ";
			out << "height:" << this->m_Bottom-this->m_Top;
			//wchar_t msg[100] = { 0 };
			//::wsprintf(msg, L"left:%f top:%f right:%f bottom:%d width:%f height:%f", this->m_Left, this->m_Top, this->m_Right, this->m_Bottom, this->m_Right - this->m_Left, this->m_Bottom - this->m_Top);
			return out.str();

		}
	protected:
		float m_Left = 0;
		float m_Top = 0;
		float m_Bottom = 0;
		float m_Right = 0;
	};
}

