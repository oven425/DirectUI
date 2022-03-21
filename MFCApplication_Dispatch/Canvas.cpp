#include "pch.h"
#include "Canvas.h"
shared_ptr<DependencyProperty<int>> Canvas::LeftPorperty;
shared_ptr<DependencyProperty<int>> Canvas::TopPorperty;

Canvas::Canvas()
{
	if (LeftPorperty == nullptr)
	{
		LeftPorperty = ::make_shared<DependencyProperty<int>>();
		LeftPorperty->Meta.PropertyChangedCallback = [&](auto obj, auto args)
		{

		};
	}
	if (TopPorperty == nullptr)
	{
		TopPorperty = ::make_shared<DependencyProperty<int>>();
		TopPorperty->Meta.PropertyChangedCallback = [&](auto obj, auto args)
		{

		};
	}
	
}

void Canvas::AddChild(shared_ptr<Control> data)
{
	this->m_Childs.push_back(data);
	data->SetParent(shared_from_this());
}

void Canvas::SetTop(shared_ptr<DependencyObject> obj, int data)
{
	obj->SetValue(Canvas::LeftPorperty, data);
}

void Canvas::SetLeft(shared_ptr<DependencyObject> obj, int data)
{
	obj->SetValue(Canvas::TopPorperty, data);
}

int Canvas::GetTop(shared_ptr<DependencyObject> obj)
{
	return obj->GetValue(Canvas::TopPorperty);
}

int Canvas::GetLeft(shared_ptr<DependencyObject> obj)
{
	return obj->GetValue(Canvas::LeftPorperty);
}