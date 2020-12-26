#pragma once
#include "CD2D_Brush.h"
#include <memory>
#include <string>
using namespace std;

namespace DirectUI
{
namespace Control
{
	class __declspec(dllexport) CControl
	{
	public:
		virtual void OnRender(ID2D1HwndRenderTarget* pRT);
	protected:
		virtual void OnSize(double width, double height, double dpiscale);
		
		friend class CContentControl;
		double m_Width = 0;
		double m_Height = 0;
		int m_Left = 0;
		int m_Top = 0;
		//double m_ActualWidth = 0;
		//double m_ActualHeight;
		//int m_ActualX = 0;
		//int m_ActualY = 0;
		double m_DpiScale = 1.0;
	public:
		wstring Name = L"";
		virtual void Measure(int width, int height) {}
		SIZE DesiredSize = { 0 };
		shared_ptr<CD2D_Brush> Background;
		
	};

}
}
	



