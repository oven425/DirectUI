#include "pch.h"
#include "CGrid.h"
using namespace DirectUI;
using namespace Control;
void CGrid::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
}