#pragma once
namespace DirectUI
{
	class __declspec(dllexport) CDirectUI_Thinkness
	{
	public:
		CDirectUI_Thinkness() {}
		CDirectUI_Thinkness(float data) { this->m_Left = this->m_Top = this->m_Right = this->m_Bottom = data; }
		CDirectUI_Thinkness(float left_right, float top_bottom)
		{
			if (left_right > 0)
			{
				this->m_Left = this->m_Right = left_right;
			}
			if (top_bottom > 0)
			{
				this->m_Top = this->m_Bottom = top_bottom;
			}
		}
		CDirectUI_Thinkness(float left, float top, float right, float bottom)
		{
			this->m_Left = left;
			this->m_Top = top;
			this->m_Right = right;
			this->m_Bottom = bottom;
		}
		void SetLeft(float data) { this->m_Left = data > 0 ? data : 0; }
		void SetTop(float data) { this->m_Top = data > 0 ? data : 0; }
		void SetRight(float data) { this->m_Right = data > 0 ? data : 0; }
		void SetBottom(float data) { this->m_Bottom = data > 0 ? data : 0; }
		float GetLeft() { return this->m_Left; }
		float GetTop() { return this->m_Top; }
		float GetRight() { return this->m_Right; }
		float GetBottom() { return this->m_Bottom; }
		bool operator==(float data) { return this->m_Bottom == data && this->m_Left == data && this->m_Right == data && this->m_Top == data; }
		bool operator==(CDirectUI_Thinkness& data) { return this->m_Bottom == data.m_Bottom&&this->m_Left == data.m_Left&&this->m_Right == data.m_Right&&this->m_Top == data.m_Top; }
		//bool operator!=(CDirectUI_Thinkness& data) { return this->m_Bottom != data.m_Bottom || this->m_Left != data.m_Left || this->m_Right != data.m_Right || this->m_Top != data.m_Top; }
		bool operator!=(const CDirectUI_Thinkness& data) { return this->m_Bottom != data.m_Bottom || this->m_Left != data.m_Left || this->m_Right != data.m_Right || this->m_Top != data.m_Top; }
		CDirectUI_Thinkness operator/(float data)
		{
			return CDirectUI_Thinkness(this->m_Left / data, this->m_Top / data, this->m_Right / data, this->m_Bottom / data);
		}
		CDirectUI_Thinkness operator*(float data)
		{
			return CDirectUI_Thinkness(this->m_Left * data, this->m_Top * data, this->m_Right * data, this->m_Bottom * data);
		}
		CDirectUI_Thinkness operator-()
		{
			return CDirectUI_Thinkness(-this->m_Left, -this->m_Top, -this->m_Right, -this->m_Bottom);
		}
		bool operator>(float data)
		{
			return this->m_Left > data || this->m_Top > data || this->m_Right > data || this->m_Bottom > data;
		}
	protected:
		float m_Left = 0;
		float m_Top = 0;
		float m_Bottom = 0;
		float m_Right = 0;
	};
}

