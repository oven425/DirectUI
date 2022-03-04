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

	//operator D2D1_SIZE_F() const throw()
	//{
	//	D2D1_SIZE_F sz = { 0 };
	//	sz.width = this->m_Width;
	//	sz.height = this->m_Height;
	//	return sz;
	//}

	operator std::function<TReturn(Args...)>() const throw()
	{
		return this->m_Func;
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

	void TT1(DependencyObject* sender, AArgs* args)
	{
		UIElement* aa = (UIElement*)sender;
	}

	void VV(DependencyObject* sender, RoutedEventArgs* args)
	{
		UIElement* aa = (UIElement*)sender;
		AArgs* bb = (AArgs*)args;
	}


	UIElement()
	{
		std::function<void(DependencyObject* sender, AArgs* args)> func = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);

		auto func1 = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
		
		auto func2 = std::bind(&UIElement::VV, this, placeholders::_1, placeholders::_2);
		


		//auto de = Delegate<void, DependencyObject*, AArgs*>(std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2));
		std::function<void(DependencyObject*, AArgs*)> f = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
		this->AddHandler(&UIElement::TestEvent, f);
		f = std::bind(&UIElement::TT1, this, placeholders::_1, placeholders::_2);
		this->AddHandler(&UIElement::TestEvent, f);

		AArgs args;
		this->RaiseEvent(&UIElement::TestEvent, &args);
	}

	map<void*, vector<IDelegate*>> m_Handlers;
	template<class T>
	void AddHandler(RoutedEvent<T>* routed, std::function<void(DependencyObject*,T*)> handler)
	{
		this->m_Handlers[routed].push_back(new Delegate<void, DependencyObject*, T*>(handler));
	}

	template<class T>
	void RemoveHandler(RoutedEvent<T>* routed) 
	{
		
	}

	template<class T>
	void RaiseEvent(RoutedEvent<T>* routed, RoutedEventArgs* args)
	{
		std::map<void*, vector<IDelegate*>>::iterator find = this->m_Handlers.find(routed);
		if (find != this->m_Handlers.end())
		{
			for (vector<IDelegate*>::iterator i = find->second.begin(); i != find->second.end(); i++)
			{
				((Delegate<void, DependencyObject*, T*>*)(*i))->invoke(this, (T*)args);


			}
		}
	}
private:

};

