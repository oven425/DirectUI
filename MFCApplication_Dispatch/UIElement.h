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
	static RoutedEvent<std::function<void()>> TestEvent;
	void TT(void* sender, AArgs* args)
	{

	}
	void AA()
	{

	}
	UIElement()
	{
		std::function<void(void*, AArgs*)> func = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
		AArgs args;
		//func(this, &args);
		std::function<void()> func1 = std::bind(&UIElement::AA, this);
		this->AddHandler(&UIElement::TestEvent, func1);
	}
	
	template<class T>
	void AddHandler(RoutedEvent<T>*, T){}
	void RemoveHandler() {}
	void RaiseEvent(RoutedEventArgs args)
	{

	}
private:

};

