#include "pch.h"
#include "Canvas.h"
DependencyProperty<int> Canvas::LeftPorperty;
DependencyProperty<int> Canvas::TopPorperty;

Canvas::Canvas()
{
	LeftPorperty.Meta.PropertyChangedCallback = [&](auto obj, auto args)
	{
		
	};
	TopPorperty.Meta.PropertyChangedCallback = [&](auto obj, auto args)
	{

	};
}

void Canvas::AddChild(shared_ptr<Control> data)
{
	this->m_Childs.push_back(data);
}

void Canvas::SetTop(shared_ptr<DependencyObject> obj, int data)
{
	obj->SetValue(&Canvas::LeftPorperty, data);
}

void Canvas::SetLeft(shared_ptr<DependencyObject> obj, int data)
{
	obj->SetValue(&Canvas::TopPorperty, data);
}

int Canvas::GetTop(shared_ptr<DependencyObject> obj)
{
	return obj->GetValue(&Canvas::TopPorperty);
}

int Canvas::GetLeft(shared_ptr<DependencyObject> obj)
{
	return obj->GetValue(&Canvas::LeftPorperty);
}