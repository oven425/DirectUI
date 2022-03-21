#pragma once
#include "DependencyObject.h"
#include "Thinckness.h"
#include <memory>
using namespace std;

class Visual:public DependencyObject
{
public:

	Visual();
	~Visual();

	string name = "";

	void SetParent(shared_ptr<Visual> data)
	{
		this->m_Parent = static_pointer_cast<DependencyObject>(data);
	}

	static shared_ptr<DependencyObject> GetParent(Visual visual)
	{
		return visual.m_Parent;
		return nullptr;
	}

	static shared_ptr<DependencyObject> GetRoot(shared_ptr<Visual> visual)
	{
		auto root = visual;
		while (root->m_Parent != nullptr)
		{
			root = static_pointer_cast<Visual>(root->m_Parent);
		}
		return static_pointer_cast<DependencyObject>(root);

		return nullptr;
	}

protected:
	shared_ptr<DependencyObject> m_Parent = nullptr;
};

