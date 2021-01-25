#include "pch.h"
#include "CD2D_PathGeometry.h"
using namespace DirectUI;

void CD2D_PathGeometry::Refresh(ID2D1RenderTarget* target)
{
	if (this->m_pPath == NULL)
	{

	}
}

void CD2D_PathGeometry::Release()
{
	if (this->m_pPath != NULL)
	{
		this->m_pPath->Release();
		this->m_pPath = NULL;
	}
}