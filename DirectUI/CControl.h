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
	protected:
		virtual void OnSize(int width, int height) { this->m_Width = width; this->m_Height = height; }
		virtual void OnRender(ID2D1HwndRenderTarget* pRT);
		friend class CContentControl;
		int m_Width = 0;
		int m_Height = 0;
		int m_Left = 0;
		int m_Top = 0;
	public:
		wstring Name = L"";
		virtual void Measure(int width, int height) {}
		SIZE DesiredSize = { 0 };
		shared_ptr<CD2D_Brush> Background;
		
	};

}
}
	



