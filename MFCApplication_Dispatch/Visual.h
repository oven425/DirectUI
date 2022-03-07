#pragma once
#include "DependencyObject.h"
#include "Thinckness.h"

class Visual:public DependencyObject
{
public:
	static DependencyProperty<string> TagProperty;
	static DependencyProperty<int> WidthProperty;
	static DependencyProperty<shared_ptr<Thinckness>> ThincknessProperty;
	void TagPropertyChange(DependencyObject obj, DependencyPropertyChangedEventArgs<string> args);
	static void TagPropertyChange1(DependencyObject obj, DependencyPropertyChangedEventArgs<string> args);
	static void WidthPropertyChange(DependencyObject* obj, DependencyPropertyChangedEventArgs<int> args);

	Visual();
	~Visual();

	static void SetTag(DependencyObject& d, string value);
	static string GetTag(DependencyObject& d);
	string name = "";

	void AddChild(Visual& data)
	{
		data.m_Parent = this;
	}


protected:
	DependencyObject* m_Parent;
};

