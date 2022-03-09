#pragma once
#include "Visual.h"
class Control : public Visual, public enable_shared_from_this<Control>
{
public:
	static DependencyProperty<int> WidthProperty;
	static DependencyProperty<int> HeightProperty;
	Control();
};

