#pragma once
#include <d2d1.h>

namespace DirectUI
{
	class __declspec(dllexport) CD2D_PathGeometry
	{
	public:
		operator ID2D1PathGeometry*()
		{
			return this->m_pPath;
		}
	protected:
		ID2D1PathGeometry* m_pPath = NULL;
	};
}


