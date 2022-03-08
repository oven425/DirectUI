#pragma once
#include "Visual.h"
class Control : public Visual
{
public:
	static DependencyProperty<int> WidthProperty;
	static DependencyProperty<int> HeightProperty;
	Control();
};

