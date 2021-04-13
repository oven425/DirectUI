#pragma once
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CheckBox : public CControl
		{
		public:
			CheckBox();
			static shared_ptr<DependencyProperty<bool>> IsCheckedProperty;
		};

	}
}

