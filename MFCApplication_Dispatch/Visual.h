#pragma once
#include "DependencyObject.h"
#include "Thinckness.h"

class Visual:public DependencyObject
{
public:
	static DependencyProperty<string> TagProperty;
	static DependencyProperty<int> WidthProperty;
	static DependencyProperty<shared_ptr<Thinckness>> ThincknessProperty;
	

	Visual();
	~Visual();

	static void SetTag(DependencyObject& d, string value);
	static string GetTag(DependencyObject& d);
	string name = "";
};

