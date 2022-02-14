#pragma once
//#include "DependencyObject.h"


#include "EventHandler.h"

template <class T>
class DependencyPropertyArgs
{
public:
	T Old;
	T New;
};

template <class T>
class DependencyProperty
{
public:
	T m_Default = T{};
	//EventHandler<DependencyObject, DependencyPropertyArgs> ValueChange;
};

