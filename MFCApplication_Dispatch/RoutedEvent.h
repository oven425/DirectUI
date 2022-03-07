#pragma once
#include <functional>
using namespace std;
#include "DependencyObject.h"
class RoutedEventArgs
{

};

template<class T>
class RoutedEvent
{
public:
	std::function<void(DependencyObject*, T*)> handler;
	RoutedEvent()
	{
		
	}
};



