#pragma once
#include <functional>
#include <d2d1.h>
#include "CDirectUI_Thinkness.h"

namespace DirectUI
{
	class __declspec(dllexport) CDirectUI_Size
	{
	public:
		CDirectUI_Size() {}
		CDirectUI_Size(std::function<void(CDirectUI_Size* data)> action) { action(this); }
		CDirectUI_Size(D2D1_SIZE_F data) { this->m_Width = data.width; this->m_Height = data.height; }
		CDirectUI_Size(float width, float height) { this->m_Width = width, this->m_Height = height; }
		void SetWidth(float data) { this->m_Width = data; }
		void SetHeight(float data) { this->m_Height = data; }
		float GetWidth() const { return this->m_Width; }
		float GetHeight() const { return this->m_Height; }
		void Clear() { this->m_Width = this->m_Height = 0; }
		operator D2D1_SIZE_F() const throw()
		{
			D2D1_SIZE_F sz = { 0 };
			sz.width = this->m_Width;
			sz.height = this->m_Height;
			return sz;
		}

		operator D2D1_RECT_F() const throw()
		{
			D2D1_RECT_F rc = { 0 };
			rc.right = this->m_Width;
			rc.bottom = this->m_Height;
			return rc;
		}

		CDirectUI_Size operator+(const CDirectUI_Thinkness& data) const throw()
		{
			CDirectUI_Size sz;
			sz.m_Width= this->m_Width - data.GetLeft() - data.GetRight();
			sz.m_Height = this->m_Height - data.GetTop() - data.GetBottom();
			return sz;
		}

		CDirectUI_Size operator-(float data) const throw()
		{
			CDirectUI_Size sz;
			sz.m_Width = this->m_Width - data;
			sz.m_Height = this->m_Height - data;
			return sz;
		}

		bool operator!=(const D2D1_SIZE_F& data) const throw()
		{
			return this->m_Height !=data.height  || this->m_Width != data.width;
		}

		bool operator!=(const CDirectUI_Size& data) const throw()
		{
			return this->m_Height != data.m_Height || this->m_Width != data.m_Width;
		}

		bool operator==(float data) const throw()
		{
			return this->m_Height == data && this->m_Width == data;
		}

		bool operator==(const CDirectUI_Size& data) const throw()
		{
			return this->m_Height == data.m_Height && this->m_Width == data.m_Width;
		}
	protected:
		float m_Width = 0;
		float m_Height = 0;
	};
}

