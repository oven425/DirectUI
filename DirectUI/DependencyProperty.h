#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>
using namespace std;

namespace DirectUI
{
	class DependencyObject;
}

namespace DirectUI
{
	class DependencyPropertyBase
	{
	public:
		wstring m_Name;
		bool AffectsArrange = false;
		bool AffectsMeasure = false;
		bool AffectsParentArrange = false;
		bool AffectsParentMeasure = false;
		bool AffectsRender = false;
	public:
		DependencyPropertyBase() {}
	};

	template<class T>
	struct DependencyPropertyChangeArgs
	{
		T OldValue;
		T NewValue;
	};

	//template<class T_Sender, class T_Args>
	//class EventHandler
	//{
	//public:
	//	void operator+=(std::function<void(const T_Sender& sender, const DependencyPropertyChangeArgs<T_Args>& args)> data)
	//	{
	//		this->m_Handlers.push_back(data);
	//	}
	//	
	//protected:
	//	vector<std::function<void(const T_Sender& sender, const DependencyPropertyChangeArgs<T_Args>& args)>> m_Handlers;
	//};
	
	template<class T>
	class DependencyProperty : public DependencyPropertyBase
	{
	public:
		//EventHandler<DependencyObject, T> Handler;
		std::function<void(const DependencyObject& sender, const DependencyPropertyChangeArgs<T>& args)> DependencyChangeHandler;
	public:
		DependencyProperty() {}
	};
}


