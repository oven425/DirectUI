#pragma once
#include "Visual.h"
#include "RoutedEvent.h"
#include <functional>
#include <any>
using namespace std;
class AArgs : public RoutedEventArgs
{
public:
	int m_V = 100;
};

class UIElement :public Visual
{
public:
	static RoutedEvent<AArgs> TestEvent;
	void TT(DependencyObject* sender, AArgs* args)
	{
		UIElement* aa = (UIElement*)sender;
	}
	void VV(DependencyObject* sender, RoutedEventArgs* args)
	{
		UIElement* aa = (UIElement*)sender;
		AArgs* bb = (AArgs*)args;
	}
	void AA()
	{

	}
	UIElement()
	{
		//vector<RoutedEvent<RoutedEventArgs>> aas;
		//aas.push_back(RoutedEvent<AArgs>());
		std::function<void(DependencyObject* sender, AArgs* args)> func = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);

		auto func1 = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
		
		auto func2 = std::bind(&UIElement::VV, this, placeholders::_1, placeholders::_2);
		using tt = decltype(std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2));
		using vv = decltype(std::bind(&UIElement::VV, this, placeholders::_1, placeholders::_2));
		auto type_name = typeid(vv).name();
		//std::forward(func1);
		//std::invoke((tt)func1_ptr, this, &AArgs());
		vector<vv> ll;
		//ll.push_back(func1);
		ll.push_back(func2);
		func1(this, &AArgs());
		func2(this, &AArgs());

		
		this->AddHandler(&UIElement::TestEvent, func);
	}
	map<void*, std::function<void(DependencyObject*, RoutedEventArgs*)>> m_Handlers;
	template<class T>
	void AddHandler(RoutedEvent<T>* routed, std::function<void(DependencyObject*,T*)> handler)
	{
		//this->m_Handlers[routed] = handler;
	}
	void RemoveHandler() {}
	void RaiseEvent(RoutedEventArgs args)
	{

	}
private:

};

