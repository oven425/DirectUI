#pragma once
#include "CD2D_Brush.h"
#include "CDirectUI_Rect.h"
#include "CTrace.h"
#include <memory>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

#include "CDependencyObject.h"

namespace DirectUI
{
namespace Control
{
	enum class Trees
	{
		Logic,
		Visual
	};
	enum class VerticalAlignments
	{
		Top,
		Center,
		Bottom,
		Stretch
	};
	enum class HorizontalAlignments
	{
		Left,
		Center,
		Right,
		Stretch
	};
	enum class Visibilitys
	{
		Visible,
		Hidden,
		Collapsed
	};
	struct MouseClickArgs
	{
		int X;
		int Y;

	};
	struct MouseMoveArgs
	{
		int X;
		int Y;

	};

	struct MouseLeftButtonDownArgs
	{
		int X;
		int Y;
	};
	struct MouseLeftButtonUpArgs
	{
		int X;
		int Y;
	};
	class __declspec(dllexport) CControl : public enable_shared_from_this<CControl>
	{
	public:
		//CControl(Trees tree= Trees::Logic)
		//	: m_Tree(tree)
		//{}

		virtual ~CControl()
		{
			this->Release();
			if (this->m_pRenderBuf != NULL)
			{
				this->m_pRenderBuf->Release();
				this->m_pRenderBuf = NULL;
			}
		}
		virtual void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi);
		virtual void OnSize(float width, float height, float dpiscale);
		void SetWidth(float data);
		void SetHieght(float data);
		void SetMinWidth(float data);
		void SetMinHieght(float data);
		void SetMaxWidth(float data);
		void SetMaxHieght(float data);
		void SetVisibility(Visibilitys data);
		Visibilitys GetVisibility() { return this->m_Visibility; }
		void SetVerticalAlignment(VerticalAlignments data);
		VerticalAlignments GetVerticalAlignment() { return this->m_VerticalAlignment; }
		void SetHorizontalAlignment(HorizontalAlignments data);
		HorizontalAlignments GetHorizontalAlignment() { return this->m_HorizontalAlignment; }
		CDirectUI_Rect& GetActualRect() { return this->m_ActualRect; }
		virtual bool HitTest(int x, int y, vector<shared_ptr<CControl>>& childs);
		void SetBackground(shared_ptr<Direct2D::CD2D_Brush> data);
		void SetEnabled(bool data);
	protected:
		static CDependencyObject<shared_ptr<CControl>, shared_ptr<CControl>> m_Parent;
		float m_Width = 0;
		float m_Height = 0;
		float m_DpiScale = 1.0;
		float m_MinWidth = 0;
		float m_MinHeight = 0;
		float m_MaxWidth = 0;
		float m_MaxHeight = 0;
		CDirectUI_Rect m_ActualRect;
		CDirectUI_Point m_ActualOffset;
		Visibilitys m_Visibility = Visibilitys::Visible;
		VerticalAlignments m_VerticalAlignment = VerticalAlignments::Stretch;
		HorizontalAlignments m_HorizontalAlignment = HorizontalAlignments::Stretch;
		virtual D2D1_SIZE_F GetSize(float width, float height);
		virtual void Release() {};
		static ID2D1Factory* m_pD2DFactory;
		CDirectUI_Rect MappingRenderRect(CDirectUI_Rect& actual_rect, D2D1_SIZE_F& measure_size, bool ignore_x=false, bool ignore_y=false);
		CDirectUI_Thinkness m_Margin;
		shared_ptr<Direct2D::CD2D_Brush> m_Background;
		bool m_IsEnabled = true;
		void CreateRenderBuf(ID2D1RenderTarget* pRT, D2D1_SIZE_F& data);
		ID2D1BitmapRenderTarget* m_pRenderBuf = NULL;
	public:
		void SetMargin(CDirectUI_Thinkness& data);
		wstring Name = L"";
		virtual void Measure(float width, float height, ID2D1RenderTarget* pRT);
		virtual void Measure(CDirectUI_Size& data, ID2D1RenderTarget* pRT);
		virtual void Arrange(float x, float y, float width, float height);
		D2D_SIZE_F DesiredSize = { 0 };
	
	public:
		virtual void OnMouseEnter(const MouseMoveArgs& args) { this->m_IsHover = true; };
		virtual void OnMouseLeave(const MouseMoveArgs& args) { this->m_IsHover = false; };
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

	protected:
		bool m_IsHover = false;
		bool m_IsPressed = false;
		float m_Opacity = 1.0;
	private:
		Trees m_Tree = Trees::Logic;
	};

}
}
	



