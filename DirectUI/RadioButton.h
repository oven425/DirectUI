#pragma once
#include "CContentControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) RadioButton : public CContentControl
		{
		public:
			RadioButton();
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void SetContent(const wchar_t* data);
			void SetIsChecked(bool data);
			bool GetIsChecked();
			__declspec(property(get = GetIsChecked, put = SetIsChecked)) bool IsChecked;
		protected:
			static shared_ptr<DependencyProperty<bool>> IsCheckedProperty;
			static shared_ptr<DependencyProperty<wstring>> GroupNameProperty;
		};
	}
}


