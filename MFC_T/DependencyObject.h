#pragma once
#include "DependencyProperty.h"

class DependencyObject
{
public:
	DependencyObject()
	{
		//GetSaves(DependencyProperty<int>());
	}
	//DependencyProperty<int> aa;
	template<typename T>
	void SetValue(DependencyProperty<T> dp, T data)
	{
	
	}

	template<typename T>
	T SetValue(DependencyProperty<T> dp)
	{

	}


};
