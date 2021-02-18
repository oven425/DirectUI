#pragma once
#include <d2d1.h>

namespace DirectUI
{
	class __declspec(dllexport) CDirectUI_Size
	{
	public:
		CDirectUI_Size() {}
		CDirectUI_Size(float width, float height) { this->m_Width = width, this->m_Height = height; }
		void SetWidth(float data) { this->m_Width = data; }
		void SetHeight(float data) { this->m_Height = data; }
		float GetWidth() { return this->m_Width; }
		float GetHeight() { return this->m_Height; }
		operator D2D1_SIZE_F() const throw()
		{
			D2D1_SIZE_F sz;
			sz.width = this->m_Width;
			sz.height = this->m_Height;
			return sz;
		}
	protected:
		float m_Width = 0;
		float m_Height = 0;
	};
}

