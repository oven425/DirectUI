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

	template<typename T_Result, typename ... Args>
	class EventHandler
	{
	public:

		void operator+=(std::function<T_Result(Args...)> data)
		{
			this->m_Handlers.push_back(data);
		}

		void Fire(Args ... args)
		{
			for (auto oo : this->m_Handlers)
			{
				oo(args...);
			}
		}
	protected:
		vector<std::function<T_Result(Args...)>> m_Handlers;
	};

	template<class T>
	struct DependencyPropertyChangeArgs
	{
		T OldValue;
		T NewValue;
	};
	
	template<class T>
	class DependencyProperty : public DependencyPropertyBase
	{
	public:
		EventHandler<void, const DependencyObject&, const DependencyPropertyChangeArgs<T>&> DependencyChangeHandler;
		//std::function<void(const DependencyObject& sender, const DependencyPropertyChangeArgs<T>& args)> DependencyChangeHandler;
		T m_Default = T{};
	public:
		DependencyProperty() {}
	};
}


