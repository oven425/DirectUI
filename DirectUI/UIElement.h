#pragma once
#include "CD2D_Brush.h"
#include "CDirectUI_Rect.h"
#include "DependencyObject.h"
#include "CTrace.h"
using namespace DirectUI;
#include <d2d1_1.h>
#include <d3d11.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

namespace DirectUI
{
	namespace Control
	{
		enum class Stretchs
		{
			None = 0,
			Fill = 1,
			Uniform = 2,
			UniformToFill = 3
		};
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
		enum class Orientations
		{
			Horizontal,
			Vertical
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
		class __declspec(dllexport) UIElement : public DependencyObject
		{
		public:
			UIElement();
			virtual ~UIElement()
			{
				this->Release();
				if (this->m_pRenderBuf != NULL)
				{
					this->m_pRenderBuf->Release();
					this->m_pRenderBuf = NULL;
				}
			}
			virtual void OnRender(ID2D1RenderTarget* pRT);
			virtual void OnSize(float width, float height, float dpiscale);
			void SetWidth(float data);
			void SetHieght(float data);
			void SetMinWidth(float data);
			void SetMinHieght(float data);
			void SetMaxWidth(float data);
			void SetMaxHieght(float data);
			void SetVisibility(Visibilitys data);
			float GetWidth() { return this->m_Width; }
			float GetHieght() { return this->m_Height; }
			Visibilitys GetVisibility() { return this->m_Visibility; }
			void SetVerticalAlignment(VerticalAlignments data);
			VerticalAlignments GetVerticalAlignment();
			__declspec(property(get = GetVerticalAlignment, put = SetVerticalAlignment)) VerticalAlignments VerticalAlignment;
			void SetHorizontalAlignment(HorizontalAlignments data);
			HorizontalAlignments GetHorizontalAlignment();
			__declspec(property(get = GetHorizontalAlignment, put = SetHorizontalAlignment)) HorizontalAlignments HorizontalAlignment;
			CDirectUI_Rect& GetActualRect() { return this->m_ActualRect; }
			virtual bool HitTest(int x, int y, vector<shared_ptr<UIElement>>& childs);
			void SetEnabled(bool data);
			virtual void Invalidate();
			virtual void InvalidateArrange();
			virtual void InvalidateMeasurce();
			virtual void SetRoot(weak_ptr<UIElement> data) { this->m_Root = data; }
		protected:
			weak_ptr<UIElement> m_Root;
			float m_Width = 0;
			float m_Height = 0;
			float m_DpiScale = 1.0;
			float m_MinWidth = 0;
			float m_MinHeight = 0;
			float m_MaxWidth = 0;
			float m_MaxHeight = 0;
			CDirectUI_Rect m_ActualRect;
			Visibilitys m_Visibility = Visibilitys::Visible;
			//VerticalAlignments m_VerticalAlignment = VerticalAlignments::Stretch;
			//HorizontalAlignments m_HorizontalAlignment = HorizontalAlignments::Stretch;
			virtual D2D1_SIZE_F GetSize(float width, float height);
			virtual void Release() {};
			static ID2D1Factory* m_pD2DFactory;
			static CDirectUI_Rect MappingRenderRect1(CDirectUI_Rect& actual_rect, const CDirectUI_Size& measure_size, HorizontalAlignments horizontalalignment, VerticalAlignments verticalalignment);
			CDirectUI_Rect MappingRenderRect(CDirectUI_Rect& actual_rect, const CDirectUI_Size& measure_size, bool ignore_x = false, bool ignore_y = false);
			bool m_IsEnabled = true;
			virtual void CreateRenderBuf(ID2D1RenderTarget* pRT, const CDirectUI_Size& data, shared_ptr<Direct2D::CD2D_Brush> background);
			ID2D1BitmapRenderTarget* m_pRenderBuf = NULL;
			
			
		public:
			void SetMargin(shared_ptr<CDirectUI_Thinkness> data);
			shared_ptr<CDirectUI_Thinkness> GetMargin();
			__declspec(property(get = GetMargin, put = SetMargin)) shared_ptr<CDirectUI_Thinkness> Margin;
			wstring Name = L"";
			virtual void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT);
			virtual void Measure(const CDirectUI_Rect& data, ID2D1RenderTarget* pRT);
			static CDirectUI_Rect MeasureMapping(const CDirectUI_Rect& rc, const CDirectUI_Size& sz, HorizontalAlignments horizontalalignment, VerticalAlignments verticalalignment);
			virtual void Arrange(const CDirectUI_Rect& data);
			D2D_SIZE_F DesiredSize = { 0 };
			CDirectUI_Rect m_MeasureRect;
		public:
			virtual void OnMouseEnter(const MouseMoveArgs& args) { this->m_IsMouseOver = true; };
			virtual void OnMouseLeave(const MouseMoveArgs& args) { this->m_IsMouseOver = false; };
			virtual void OnMouseMove(const MouseMoveArgs& args) {};
			virtual void OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args) { this->m_IsPressed = true; };
			virtual void OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args) { this->m_IsPressed = false; };
			virtual void OnIsEnabled(bool data) { this->m_IsEnabled = data; }
			std::function<void(shared_ptr<UIElement> sender, const MouseClickArgs& args)> MouseClickHandler;
			std::function<void(shared_ptr<UIElement> sender, const MouseMoveArgs& args)> MouseEnterHandler;
			std::function<void(shared_ptr<UIElement> sender, const MouseMoveArgs& args)> MouseLeaveHandler;
			std::function<void(shared_ptr<UIElement> sender, const MouseMoveArgs& args)> MouseMoveHandler;
			std::function<void(shared_ptr<UIElement> sender, const MouseLeftButtonDownArgs& args)> MouseLeftButtonDownHandler;
			std::function<void(shared_ptr<UIElement> sender, const MouseLeftButtonUpArgs& args)> MouseLeftButtonUpHandler;
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
		protected:
			static shared_ptr<DependencyProperty<shared_ptr<CDirectUI_Thinkness>>> MarginProperty;
			static shared_ptr<DependencyProperty<int>> HorizontalAlignmentProperty;
			static shared_ptr<DependencyProperty<int>> VerticalAlignmentProperty;
		};
	}
}


