#pragma once
#include <stack>
using namespace std;
//template <class T>
//class IBrush
//{
//	T m_Brush = T{};
//};

//virtual operator ID2D1Brush*() { return NULL; }

class Brush
{
public:
	virtual operator ID2D1Brush* () { return NULL; }
};


class SoildBrush:Brush
{
public:

	D2D1::ColorF m_Color;
	operator ID2D1Brush* () override
	{
		return m_Brush;
	}
private:
	CComPtr<ID2D1SolidColorBrush> m_Brush;

};
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

