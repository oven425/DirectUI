#pragma once
#include "CControl.h"
namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CBorder : public CControl
		{
		public:
			unique_ptr<CD2D_Brush> BorderBrush;
			int BorderThickness = 0;
			int CornerRadius = 0;
			void Measure(int width, int height);

		protected:
			void OnSize(int width, int height);
			void OnRender();
		};
	}
}


