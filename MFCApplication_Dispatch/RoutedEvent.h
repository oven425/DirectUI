#pragma once
#include <functional>
using namespace std;
#include "DependencyObject.h"



//template<class T>
class RoutedEvent
{
public:
	//std::function<void(DependencyObject*, T*)> handler;
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

	//std::function<void(DependencyObject*, decltype(this))> handler;

};

