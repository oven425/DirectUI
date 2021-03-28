#pragma once
#include "CContentControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) RadioButton : public CContentControl
		{
		public:
			void SetContent(const wchar_t* data);
			static DependencyProperty IsCheckedProperty;
			static DependencyProperty GroupNameProperty;
		};
	}
}


