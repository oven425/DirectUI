#pragma once
#include "CControl.h"
namespace DirectUI
{
	namespace Control
	{
		struct  DragStartedEventArgs
		{
			float HorizontalOffset = 0;
			float VerticalOffset = 0;
		};
		struct  DragDeltaEventArgs
		{
			float HorizontalChange = 0;
			float VerticalChange = 0;
		};
		struct  DragCompletedEventArgs
		{
			float HorizontalChange = 0;
			float VerticalChange = 0;
		};
		class __declspec(dllexport) CThumb : public CControl
		{
		public:
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
			std::function<void(const shared_ptr<CControl> sender, const DragStartedEventArgs& args)> DragStartedHandler;
			std::function<void(const shared_ptr<CControl> sender, const DragDeltaEventArgs& args)> DragDeltaHandler;
			std::function<void(const shared_ptr<CControl> sender, const DragCompletedEventArgs& args)> DragCompletedHandler;
			virtual void OnMouseMove(const MouseMoveArgs& args) override;
			virtual void OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args) override;
			virtual void OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args) override;
		protected:
			CDirectUI_Point m_LastPoint;
			CDirectUI_Point m_Offset;
		};
	}
}


