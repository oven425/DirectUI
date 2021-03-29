#pragma once
#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) Track : public CControl
		{
		public:
			void SetOrientation(Orientations data);
			Orientations GetOrientations() { return this->m_Orientation; }
		protected:
			Orientations m_Orientation;
		};
	}
}


