#pragma once
#include "CControl.h"
namespace DirectUI
{
	namespace Control
	{
		struct  DragStartedEventArgs
		{
			float X;
			float Y;
		};
		struct  DragDeltaEventArgs
		{
			float X;
			float Y;
		};
		struct  DragCompletedEventArgs
		{
			float X;
			float Y;
		};
		class __declspec(dllexport) CThumb : public CControl
		{
		public:
			void OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Arrange(float x, float y, float width, float height) override;
			std::function<void(const shared_ptr<CThumb> sender, const DragStartedEventArgs& args)> DragStartedHandler;
			std::function<void(const shared_ptr<CThumb> sender, const DragDeltaEventArgs& args)> DragDeltaHandler;
			std::function<void(const shared_ptr<CThumb> sender, const DragCompletedEventArgs& args)> DragCompletedHandler;
			virtual void OnMouseMove(const MouseMoveArgs& args) override;
			virtual void OnMouseLeftButtonDown(const MouseLeftButtonDownArgs& args) override;
			virtual void OnMouseLeftButtonUp(const MouseLeftButtonUpArgs& args) override;
		};
	}
}


