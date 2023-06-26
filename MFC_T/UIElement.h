#pragma once
#include <stack>
using namespace std;
#include "Brush.h"



class UIElement
{
public:
	Brush Background;
	unsigned int m_Width;
	unsigned int m_Height;
	virtual void Render()
	{

	}
};

class StackPanel :UIElement
{
public:
	stack<UIElement> m_Childs;
	void Render() override
	{

	}
};

