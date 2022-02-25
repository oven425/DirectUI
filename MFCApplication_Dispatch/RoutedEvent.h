#pragma once
#include <functional>
using namespace std;
#include "DependencyObject.h"
class RoutedEventArgs
{

};

template<class T, class A=std::queue<T>>
class RoutedEvent
{
public:
	A aa;

	std::function<void(DependencyObject*, T*)> handler;
	//T handler;
	RoutedEvent()
	{
		
	}
};



