#pragma once
#include "Visual.h"
#include "RoutedEvent.h"
#include <functional>
using namespace std;

class IDelegate
{
public:
	virtual void Check() = 0;
};

template<typename TReturn, typename... Args>
class Delegate :public IDelegate
{
public:
	void Check()
	{

	}
	Delegate() {}
	Delegate(std::function<TReturn(Args...)> func)
	{
		this->m_Func = func;
	}
	TReturn invoke(Args... data)
	{
		return m_Func(data...);
	}

	void operator=(std::function<TReturn(Args...)> func)
	{
		this->m_Func = func;
	}
protected:
	std::function<TReturn(Args...)> m_Func;
};

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
		std::function<void(DependencyObject* sender, AArgs* args)> func = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);

		auto func1 = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
		
		auto func2 = std::bind(&UIElement::VV, this, placeholders::_1, placeholders::_2);
		
		using tt = decltype(std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2));
		using vv = decltype(std::bind(&UIElement::VV, this, placeholders::_1, placeholders::_2));
		using ww = std::function<void(DependencyObject*, RoutedEventArgs*)>;
		auto type_name = typeid(vv).name();

		//func1(this, &AArgs());
		//func2(this, &AArgs());

		//void* oi = (void*)&func1;
		//auto f = (tt*)oi;
		//(*f)(this, &AArgs());
		
		std::function<void(DependencyObject*, AArgs*)> aa1 = func1;
		
		//std::function<void(DependencyObject*, RoutedEventArgs*)> aa2 = aa1;



		//vector<IDelegate*> ii;
		//Delegate<void, DependencyObject*, AArgs*> delegate_aargs;
		//delegate_aargs = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
		//delegate_aargs.invoke(this, &AArgs());
		//ii.push_back(&delegate_aargs);



		std::function<void(DependencyObject*, AArgs*)> f = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
		this->AddHandler(&UIElement::TestEvent, f);
		AArgs args;
		this->RaiseEvent(args);
	}
	//map<void*, vector<void*>> m_Handlers;
	map<void*, vector<IDelegate*>> m_Handlers;
	template<class T>
	void AddHandler(RoutedEvent<T>* routed, std::function<void(DependencyObject*,T*)> handler)
	{
		this->m_Handlers[routed].push_back(new Delegate<void, DependencyObject*, T*>(handler));
		//void* oi = (void*)&handler;
		//this->m_Handlers[routed].push_back(oi);
	}

	template<class T>
	void RemoveHandler(RoutedEvent<T>* routed) 
	{
		
	}

	void RaiseEvent(RoutedEventArgs args)
	{

	}
private:

};

