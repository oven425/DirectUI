#pragma once
#include "CContentControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) RadioButton : public CContentControl
		{
		public:
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void SetContent(const wchar_t* data);
			//static DependencyProperty IsCheckedProperty;
			//static DependencyProperty GroupNameProperty;
		};
	}
}


