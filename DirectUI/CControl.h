#pragma once
#include "CD2D_Brush.h"
#include "CDirectUI_Rect.h"
#include "CTrace.h"
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

namespace DirectUI
{
namespace Control
{
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
	class __declspec(dllexport) CControl
	{
	public:
		CControl() {}
		virtual ~CControl() { this->Release(); }
		virtual void OnRender(ID2D1RenderTarget* pRT);
		virtual void OnSize(float width, float height, float dpiscale);
		void SetWidth(float data) { this->m_Width = data; }
		void SetHieght(float data) { this->m_Height = data; }
		void SetMinWidth(float data) { this->m_MinWidth = data; }
		void SetMinHieght(float data) { this->m_MinHeight = data; }
		void SetMaxWidth(float data) { this->m_MaxWidth = data; }
		void SetMaxHieght(float data) { this->m_MaxHeight = data; }
		void SetVisibility(Visibilitys data) { this->m_Visibility = data; }
		Visibilitys GetVisibility() { return this->m_Visibility; }
		void SetVerticalAlignment(VerticalAlignments data) { this->m_VerticalAlignment = data; }
		VerticalAlignments GetVerticalAlignment() { return this->m_VerticalAlignment; }
		void SetHorizontalAlignment(HorizontalAlignments data) { this->m_HorizontalAlignment = data; }
		HorizontalAlignments GetHorizontalAlignment() { return this->m_HorizontalAlignment; }
		CDirectUI_Rect& GetActualRect() { return this->m_ActualRect; }
	protected:
		friend class CContentControl;
		float m_Width = 0;
		float m_Height = 0;
		float m_DpiScale = 1.0;
		float m_MinWidth = 0;
		float m_MinHeight = 0;
		float m_MaxWidth = 0;
		float m_MaxHeight = 0;
		CDirectUI_Rect m_ActualRect;
		Visibilitys m_Visibility = Visibilitys::Visible;
		VerticalAlignments m_VerticalAlignment = VerticalAlignments::Stretch;
		HorizontalAlignments m_HorizontalAlignment = HorizontalAlignments::Stretch;
		virtual D2D1_SIZE_F GetSize(float width, float height);
		virtual void Release() {};
		static ID2D1Factory* m_pD2DFactory;
	public:
		CDirectUI_Thinkness Margin;
		wstring Name = L"";
		virtual void Measure(float width, float height, ID2D1RenderTarget* pRT);
		virtual void Arrange(float x, float y, float width, float height);
		D2D_SIZE_F DesiredSize = { 0 };
		shared_ptr<CD2D_Brush> Background;
		
	};

}
}
	



