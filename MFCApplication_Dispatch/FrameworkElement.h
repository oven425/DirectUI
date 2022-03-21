#pragma once
#include "UIElement.h"

class FrameworkElement:public UIElement
{
public:
	FrameworkElement();
	static shared_ptr<DependencyProperty<double>> WidthProperty;
	static shared_ptr<DependencyProperty<double>> HeightProperty;
	void SetWidth(double data);
	void SetHeight(double data);
	double GetWidth();
	double GetHeight();
protected:
	virtual Size MeasureOverride(Size& data) { return Size(); }
};

