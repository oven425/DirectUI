#pragma once
#include "Control.h"
class Canvas : public Control
{
public:
	Canvas();
	static DependencyProperty<int> LeftPorperty;
	static DependencyProperty<int> TopPorperty;
	void AddChild(shared_ptr<Control> data);
	static void SetTop(shared_ptr<DependencyObject> obj, int data);
	static void SetLeft(shared_ptr<DependencyObject> obj, int data);
	static int GetTop(shared_ptr<DependencyObject> obj);
	static int GetLeft(shared_ptr<DependencyObject> obj);
protected:
	vector<shared_ptr<Control>> m_Childs;
};

