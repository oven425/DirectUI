#pragma once
#include "CControl.h"
namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CBorder : public CControl
		{
			void OnSize(int width, int height);
			void OnRender();
		};
	}
}


