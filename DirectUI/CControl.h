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
		virtual ~CControl()
		{
			this->Release();
			if (this->m_pRenderBuf != NULL)
			{
				this->m_pRenderBuf->Release();
				this->m_pRenderBuf = NULL;
			}
		}
		void OnRender(ID2D1RenderTarget* pRT) override;
		void OnSize(float width, float height, float dpiscale) override;
		//void SetWidth(float data);
		//void SetHieght(float data);
		//void SetMinWidth(float data);
		//void SetMinHieght(float data);
		//void SetMaxWidth(float data);
		//void SetMaxHieght(float data);
		//void SetVisibility(Visibilitys data);
		//float GetWidth() { return this->m_Width; }
		//float GetHieght() { return this->m_Height; }
		//Visibilitys GetVisibility() { return this->m_Visibility; }
		//void SetVerticalAlignment(VerticalAlignments data);
		//VerticalAlignments GetVerticalAlignment() { return this->m_VerticalAlignment; }
		//void SetHorizontalAlignment(HorizontalAlignments data);
		//HorizontalAlignments GetHorizontalAlignment() { return this->m_HorizontalAlignment; }
		//CDirectUI_Rect& GetActualRect() { return this->m_ActualRect; }
		virtual bool HitTest(int x, int y, vector<shared_ptr<CControl>>& childs);
		void SetBackground(shared_ptr<Direct2D::CD2D_Brush> data);
		shared_ptr<Direct2D::CD2D_Brush> GetBackground();
		//void SetEnabled(bool data);
		virtual void Invalidate();
		virtual void InvalidateArrange();
		virtual void InvalidateMeasurce();
		virtual void SetRoot(weak_ptr<CControl> data) { this->m_Root = data; }
		__declspec(property(get = GetBackground, put = SetBackground)) shared_ptr<Direct2D::CD2D_Brush> Background;
	protected:
		weak_ptr<CControl> m_Root;
		//float m_Width = 0;
		//float m_Height = 0;
		//float m_DpiScale = 1.0;
		//float m_MinWidth = 0;
		//float m_MinHeight = 0;
		//float m_MaxWidth = 0;
		//float m_MaxHeight = 0;
		CDirectUI_Rect m_ActualRect;
		//Visibilitys m_Visibility = Visibilitys::Visible;
		//VerticalAlignments m_VerticalAlignment = VerticalAlignments::Stretch;
		//HorizontalAlignments m_HorizontalAlignment = HorizontalAlignments::Stretch;
		virtual D2D1_SIZE_F GetSize(float width, float height);
		virtual void Release() {};
		static ID2D1Factory* m_pD2DFactory;
		CDirectUI_Rect MappingRenderRect(CDirectUI_Rect& actual_rect, const CDirectUI_Size& measure_size, bool ignore_x=false, bool ignore_y=false);
		CDirectUI_Thinkness m_Margin;
		//shared_ptr<Direct2D::CD2D_Brush> m_Background;
		bool m_IsEnabled = true;
		void CreateRenderBuf(ID2D1RenderTarget* pRT, const CDirectUI_Size& data, bool autofillbackground=true);
		ID2D1BitmapRenderTarget* m_pRenderBuf = NULL;
	public:
		void SetMargin(CDirectUI_Thinkness& data);
		wstring Name = L"";
		virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT);
		virtual void Arrange(const CDirectUI_Rect& data);
		D2D_SIZE_F DesiredSize = { 0 };
	public:
		virtual void OnMouseEnter(const MouseMoveArgs& args) { this->m_IsMouseOver = true; };
		virtual void OnMouseLeave(const MouseMoveArgs& args) { this->m_IsMouseOver = false; };
		virtual void OnMouseMove(const MouseMoveArgs& args) {};
		virtual void OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args) { this->m_IsPressed = true; };
		virtual void OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args) { this->m_IsPressed = false; };
		virtual void OnIsEnabled(bool data) { this->m_IsEnabled = data; }
		std::function<void(shared_ptr<CControl> sender, const MouseClickArgs& args)> MouseClickHandler;
		std::function<void(shared_ptr<CControl> sender, const MouseMoveArgs& args)> MouseEnterHandler;
		std::function<void(shared_ptr<CControl> sender, const MouseMoveArgs& args)> MouseLeaveHandler;
		std::function<void(shared_ptr<CControl> sender, const MouseMoveArgs& args)> MouseMoveHandler;
		std::function<void(shared_ptr<CControl> sender, const MouseLeftButtonDownArgs& args)> MouseLeftButtonDownHandler;
		std::function<void(shared_ptr<CControl> sender, const MouseLeftButtonUpArgs& args)> MouseLeftButtonUpHandler;
		void SetTree(Trees data) { this->m_Tree = data; }
		Trees GetTree() { return this->m_Tree; }
		bool GetCaptureMouse() { return this->m_IsCaptureMouse; }
		void SetCaptureMouse(bool data);
		bool GetIsMouseOver() { return this->m_IsMouseOver; }
	protected:
		bool m_IsMouseOver = false;
		bool m_IsPressed = false;
		bool m_IsCaptureMouse = false;
		float m_Opacity = 1.0;
	private:
		Trees m_Tree = Trees::Logic;
	public:
		static shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>> BackgroundProperty;
		static void BackgroundPropertyChange(const DependencyObject& sender, const DependencyPropertyChangeArgs< Direct2D::CD2D_Brush>& args);
	};

}
}
	



