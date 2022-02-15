#pragma once
//#include "DependencyObject.h"

#include <functional>
using namespace std;

#include "EventHandler.h"
class DependencyObject;
template <class T>
class DependencyPropertyArgs
{
public:
	T Old;
	T New;
};

template <class T>
class PropertyMetadata
{
public:
	T Default;
	std::function<void(DependencyObject obj, DependencyPropertyArgs<T> args)> PropertyChangedCallback;
};

template <class T>
class DependencyProperty
{
public:
	T m_Default = T{};
	EventHandler<DependencyObject, DependencyPropertyArgs<T>> PropertyChangedCallback;
};

