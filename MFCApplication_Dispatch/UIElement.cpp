#include "pch.h"
#include "UIElement.h"
RoutedEvent UIElement::TestEvent;
UIElement::UIElement()
{
	std::function<void(DependencyObject* sender, AArgs* args)> func = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);

	auto func1 = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);

	auto func2 = std::bind(&UIElement::VV, this, placeholders::_1, placeholders::_2);


	//auto de = Delegate<void, DependencyObject*, AArgs*>(std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2));
	std::function<void(DependencyObject*, AArgs*)> f = std::bind(&UIElement::TT, this, placeholders::_1, placeholders::_2);
	this->AddHandler(&UIElement::TestEvent, f);
	this->AddHandler(&UIElement::TestEvent, f);
	f = std::bind(&UIElement::TT1, this, placeholders::_1, placeholders::_2);
	this->AddHandler(&UIElement::TestEvent, f);
	this->RemoveHandler(&UIElement::TestEvent, f);
	AArgs args(&UIElement::TestEvent);
	this->RaiseEvent(&args);
	
	//this->RaiseEvent(&UIElement::TestEvent, &args);
}


void UIElement::RaiseEvent(RoutedEventArgs* args)
{
	string nn = "";
	auto handlers = this->m_Handlers.find(args->m_RoutedEvent);
	if (handlers != this->m_Handlers.end())
	{
		for (auto i = handlers->second.begin(); i != handlers->second.end(); i++)
		{
			for (auto j = i->second.begin(); j != i->second.end(); j++)
			{
				auto a = j->get();
				Delegate<void, DependencyObject*, decltype(args)>* aa = (Delegate<void, DependencyObject*, decltype(args)>*)a;
				aa->invoke(this, args);

				auto bb = static_cast<Delegate<void, DependencyObject*, decltype(args)>*>(a);
				bb->invoke(this, args);

			}
		}

	}
}

void UIElement::CaptureMouse()
{

}

void UIElement::ReleaseMouseCapture()
{

}