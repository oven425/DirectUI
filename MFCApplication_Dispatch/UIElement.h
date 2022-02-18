#pragma once
#include "Visual.h"
#include "RoutedEvent.h"
#include<functional>
using namespace std;
class AArgs : public RoutedEventArgs
{

};
class UIElement :public Visual
{
public:
	static RoutedEvent TestEvent;
	void TT(void* sender, AArgs* args)
	{

	}
	UIElement()
	{
		//std::function<void(void*, RoutedEventArgs*)> func = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
		//AArgs args;
		//func(this, &args);
	}
	
	void AddHandler(){}
	void RemoveHandler() {}
	void RaiseEvent(RoutedEventArgs args)
	{

	}
};

