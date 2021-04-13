#include "pch.h"
#include "Line.h"
using namespace DirectUI;
using namespace Shapes;

shared_ptr<DependencyProperty<float>> Line::X1Property;
shared_ptr<DependencyProperty<float>> Line::X2Property;
shared_ptr<DependencyProperty<float>> Line::Y1Property;
shared_ptr<DependencyProperty<float>> Line::Y2Property;

Line::Line()
{
	if (!X1Property)
	{
		X1Property = ::make_shared<DependencyProperty<float>>();
	}
	if (!X2Property)
	{
		X2Property = ::make_shared<DependencyProperty<float>>();
	}
	if (!Y1Property)
	{
		Y1Property = ::make_shared<DependencyProperty<float>>();
	}
	if (!Y2Property)
	{
		Y2Property = ::make_shared<DependencyProperty<float>>();
	}
}

void Line::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{

}

void Line::Arrange(const CDirectUI_Rect& data)
{

}

void Line::OnRender(ID2D1RenderTarget* pRT)
{

}
