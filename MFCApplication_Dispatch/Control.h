#pragma once
#include "DependencyObject.h"
class Control : public DependencyObject
{
public:
	static DependencyProperty<int> WidthProperty;
	static DependencyProperty<int> HeightProperty;
	Control();
};

