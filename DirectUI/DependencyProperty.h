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

	template<typename T>
	class EventHandler
	{
	public:
		void operator+=(const T& data)
		{

			this->m_Handlers.push_back(data);
		}

		void Fire(int data)
		{
			for (auto oo : this->m_Handlers)
			{
				oo(data);
			}
		}
	protected:
		vector<T> m_Handlers;
	};
	
	template<class T>
	class DependencyProperty : public DependencyPropertyBase
	{
	public:
		//EventHandler<std::function<void(const DependencyObject& sender, const DependencyPropertyChangeArgs<T>& args)>> DependencyChangeHandler;
		std::function<void(const DependencyObject& sender, const DependencyPropertyChangeArgs<T>& args)> DependencyChangeHandler;
		
	public:
		DependencyProperty() {}
	};
}


