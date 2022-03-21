#pragma once
#include "FrameworkElement.h"

class Control : public FrameworkElement, public enable_shared_from_this<Control>
{
public:
	static DependencyProperty<int> WidthProperty;
	static DependencyProperty<int> HeightProperty;
	Control();
};

