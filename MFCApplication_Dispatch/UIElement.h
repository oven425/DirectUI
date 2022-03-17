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

template<typename TReturn, typename... TParam>
class Delegate :public IDelegate
{
public:
	void Check()
	{

	}
	Delegate() {}
	Delegate(std::function<TReturn(TParam...)> func)
	{
		this->m_Func = func;
	}
	TReturn invoke(TParam... data)
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

	operator std::function<TReturn(TParam...)>() const throw()
	{
		return this->m_Func;
	}

	void operator=(std::function<TReturn(TParam...)> func)
	{
		this->m_Func = func;
	}
protected:
	std::function<TReturn(TParam...)> m_Func;
};

class AArgs : public RoutedEventArgs
{
public:
	AArgs() {}
	AArgs(RoutedEvent* routedevent)
		: RoutedEventArgs(routedevent)
	{

	}
	int m_V = 100;
};

class UIElement :public Visual
{
public:
	static RoutedEvent TestEvent;
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
	//MwndSource->HwndMouseInputProvider->
	//PreviewMouseUpEvent
	//HwndMouseInputProvider
	//HwndWrapper _wndProc
	//InputManager RequestContinueProcessingStagingArea
	UIElement();

	
	template<class T>
	void AddHandler(RoutedEvent* routed, std::function<void(DependencyObject*,T*)> handler)
	{
		auto nn = typeid(handler).name();
		this->m_Handlers[routed][nn].push_back(::make_unique<Delegate<void, DependencyObject*, T*>>(handler));
	}

	template<class T>
	void RemoveHandler(RoutedEvent* routed, std::function<void(DependencyObject*, T*)> handler)
	{
		auto nn = typeid(handler).name();
		auto handlers = this->m_Handlers.find(routed);
		if (handlers != this->m_Handlers.end())
		{
			std::map<string, vector<unique_ptr<IDelegate>>>::iterator delegates = handlers->second.find(nn);
			if (delegates != handlers->second.end())
			{
				if (delegates->second.empty() == false)
				{
					delegates->second.erase(delegates->second.begin());
				}
			}
		}
	}
	void RaiseEvent(RoutedEventArgs* args);
	void CaptureMouse();
	void ReleaseMouseCapture();
private:
	map<void*, map<string, vector<unique_ptr<IDelegate>>>> m_Handlers;
};

