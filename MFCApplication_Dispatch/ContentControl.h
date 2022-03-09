#pragma once
#include "Control.h"
class ContentControl : public Control
{
public:
	void SetChild(shared_ptr<Control> data)
	{
		if (data != nullptr)
		{
			this->m_Child = data;
			data->SetParent(shared_from_this());
		}
		else
		{
			this->m_Child->SetParent(nullptr);
			this->m_Child = data;
		}
	}
protected:
	shared_ptr<Control> m_Child;
};

