#pragma once
namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CDirectUI_Thinkness
		{
		public:
			CDirectUI_Thinkness() {}
			CDirectUI_Thinkness(int data) { this->m_Left = this->m_Top = this->m_Right = this->m_Bottom = data; }
			CDirectUI_Thinkness(int left_right, int top_bottom) { this->m_Left = this->m_Right = left_right; this->m_Top = this->m_Bottom = top_bottom; }
			CDirectUI_Thinkness(int left, int right, int top, int bottom) { this->m_Left = left, this->m_Right = right; this->m_Top = top; this->m_Bottom = bottom; }
			void SetLeft(int data) { this->m_Left = data; }
			void SetTop(int data) { this->m_Top = data; }
			void SetRight(int data) { this->m_Right = data; }
			void SetBottom(int data) { this->m_Bottom = data; }
			int GetLeft() { return this->m_Left; }
			int GetTop() { return this->m_Top; }
			int GetRight() { return this->m_Right; }
			int GetBottom() { return this->m_Bottom; }
		protected:
			int m_Left = 0;
			int m_Top = 0;
			int m_Bottom = 0;
			int m_Right = 0;
		};
	}
}
