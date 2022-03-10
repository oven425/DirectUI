#pragma once
#include "UIElement.h"

class Control : public UIElement, public enable_shared_from_this<Control>
{
public:
	static DependencyProperty<int> WidthProperty;
	static DependencyProperty<int> HeightProperty;
	Control();
};

