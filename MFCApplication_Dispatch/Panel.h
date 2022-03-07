#pragma once
#include "Control.h"
class Panel : public Control
{
public:
	static DependencyProperty<int> ZIndexProperty;
};

