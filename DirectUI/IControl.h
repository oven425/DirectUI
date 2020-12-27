#pragma once
#include <memory>
#include <string>
using namespace std;
#include "CD2D_Brush.h"
#include <d2d1.h>

namespace DirectUI
{
	namespace Control
	{
		class IControl
		{
		public:
			virtual void OnRender(ID2D1HwndRenderTarget* pRT)=0;
			virtual void OnSize(double width, double height, double dpiscale)=0;
			void SetWidth(int data) { this->m_Width = data; }
			void SetHieght(int data) { this->m_Height = data; }
		protected:

			friend class CContentControl;
			double m_Width = 0;
			double m_Height = 0;
			int m_Left = 0;
			int m_Top = 0;
			double m_ActualWidth = 0;
			double m_ActualHeight;
			double m_ActualX = 0;
			double m_ActualY = 0;
			double m_DpiScale = 1.0;
			double Margin_Left = 0;
			double Margin_Top = 0;
			double Margin_Right = 0;
			double Margin_Bottom = 0;
		public:
			wstring Name = L"";
			virtual void Measure(double width, double height)
			{
				this->DesiredSize.cx = width;
				if (this->m_Width > 0)
				{
					this->DesiredSize.cx = this->m_Width;
				}
				this->DesiredSize.cy = height;
				if (this->m_Height > 0)
				{
					this->DesiredSize.cy = this->m_Height;
				}
			}
			virtual void Arrange(double x, double y, double width, double height)
			{
				this->m_ActualX = x;
				this->m_ActualY = y;
				this->m_ActualWidth = width;
				this->m_ActualHeight = height;
			}
			SIZE DesiredSize = { 0 };
			shared_ptr<CD2D_Brush> Background;
		};
	}
}

