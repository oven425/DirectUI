#pragma once
//#include "DependencyObject.h"

#include <functional>
using namespace std;

#include "EventHandler.h"
class DependencyObject;
template <class T>
class DependencyPropertyChangedEventArgs
{
public:
	T OldValue;
	T NewValue;
};

template <class T>
class PropertyMetadata
{
public:
	T Default;
	std::function<void(DependencyObject* obj, DependencyPropertyChangedEventArgs<T> args)> PropertyChangedCallback;
};

template <class T>
class DependencyProperty
{
public:
	DependencyProperty() {}
	virtual ~DependencyProperty() {}
public:
	PropertyMetadata<T> Meta;
};

