#pragma once
#include "Control.h"
class Canvas : public Control
{
public:
	void AddChild(shared_ptr<Control> data)
	{
		this->m_Childs.push_back(data);
	}
protected:
	vector<shared_ptr<Control>> m_Childs;
};

