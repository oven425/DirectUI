#pragma once
#include "DependencyObject.h"
#include "Thinckness.h"

class Visual:public DependencyObject
{
public:
	static DependencyProperty<int> WidthProperty;
	static DependencyProperty<shared_ptr<Thinckness>> ThincknessProperty;
	Visual();
	~Visual();
};

