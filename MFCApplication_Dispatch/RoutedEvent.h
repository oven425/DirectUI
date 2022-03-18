#pragma once
#include <functional>
using namespace std;
#include "DependencyObject.h"

class RoutedEvent
{
public:
	RoutedEvent()
	{
		
	}
};

class RoutedEventArgs
{
public:
	RoutedEventArgs() {}
	RoutedEventArgs(RoutedEvent* routedevent)
	{
		this->m_RoutedEvent = routedevent;
	}
	RoutedEvent* m_RoutedEvent;
};

