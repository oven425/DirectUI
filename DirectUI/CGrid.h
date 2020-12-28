#pragma once
#include <list>
#include <map>
using namespace std;

#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CGrid: public CControl
		{
		public:
			void AddChild(shared_ptr<CControl> data);
		protected:
			list<shared_ptr<CControl>> m_Childs;
		};
	}
}

