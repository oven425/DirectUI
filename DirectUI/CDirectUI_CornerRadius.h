#pragma once
namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CDirectUI_CornerRadius
		{
		public:
			CDirectUI_CornerRadius(float data)
			{
				if (data > 0)
				{
					this->m_BottomLeft = this->m_BottomRight = this->m_TopLeft = this->m_TopRight = data;
				}
			}
			CDirectUI_CornerRadius(float topleft, float topright, float bottomright, float bottomleft)
			{
				this->m_BottomLeft = bottomleft > 0 ? bottomleft : 0;
				this->m_BottomRight = bottomright > 0 ? bottomright : 0;
				this->m_TopLeft = topleft > 0 ? topleft : 0;
				this->m_TopRight = topright > 0 ? topright : 0;
			}

			float GetBottomLeft() { return this->m_BottomLeft; }
			float GetBottomRight() { return this->m_BottomRight; }
			float GetTopLeft() { return this->m_TopLeft; }
			float GetTopRight() { return this->m_TopRight; }
			bool operator==(CDirectUI_CornerRadius& data)
			{
				return this->m_BottomLeft == data.m_BottomLeft&&this->m_BottomRight == data.m_BottomRight&&this->m_TopLeft == data.m_TopLeft&&this->m_TopRight == data.m_TopRight;
			}
			CDirectUI_CornerRadius operator/(float data)
			{
				return CDirectUI_CornerRadius(this->m_TopLeft / data, this->m_TopRight / data, this->m_BottomRight / data, this->m_BottomLeft / data);
			}
		protected:
			float m_BottomLeft = 0;
			float m_BottomRight = 0;
			float m_TopLeft = 0;
			float m_TopRight = 0;
		};
	}
}


