#pragma once

#include "CTrace.h"
#include <memory>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
#include "UIElement.h"
//#include "CDependencyObject.h"

namespace DirectUI
{
namespace Control
{
	
	class __declspec(dllexport) CControl : public UIElement
	{
	public:
		CControl();
		virtual ~CControl() {}
		void CreateRenderBuf(ID2D1RenderTarget* pRT, const CDirectUI_Size& data);
		void SetBackground(shared_ptr<Direct2D::CD2D_Brush> data);
		shared_ptr<Direct2D::CD2D_Brush> GetBackground();
		__declspec(property(get = GetBackground, put = SetBackground)) shared_ptr<Direct2D::CD2D_Brush> Background;
	protected:
		virtual void Release() {};
	public:
		static shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>> BackgroundPropertyInstance();
		static shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>> BackgroundProperty;		
		static void BackgroundPropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs< Direct2D::CD2D_Brush>& args);
	};

}
}
	



