#pragma once
//#include "UIElement.h"
//using namespace DirectUI;
//using namespace Control;

#include "DependencyProperty.h"
using namespace DirectUI;

//#include "UIElement.h"
namespace DirectUI
{
	namespace Control
	{
		class UIElement;
	}
}

namespace DirectUI
{
	class DependencyObject;
}



namespace DirectUI
{
	namespace Data
	{
		enum class BindingModes
		{
			TwoWay,
			OneWay,
			OneTime,
			OneWayToSource
		};
		template<typename T_Dst, typename T_Src>
		class __declspec(dllexport) IValueConverter
		{
		public:
			virtual T_Dst Convert(T_Src value) = 0;
		};

		class __declspec(dllexport) BindingBase
		{
		public:
			wstring m_Name;
			template<typename T>
			void SetSource(shared_ptr<DependencyProperty<T>> dp, shared_ptr<DirectUI::Control::UIElement> ui)
			{
				if (dp)
				{
					dp->DependencyChangeHandler = [](const DependencyObject& sender, const DependencyPropertyChangeArgs<T>& args)
					{
					};
				}
			}

			template<typename T>
			void SetTarget(shared_ptr<DependencyProperty<T>> dp, shared_ptr<DirectUI::Control::UIElement> ui)
			{
				m_TargetDP = dp;
				this->m_Target = ui;
				if (!dp && !ui)
				{
					
				}
			}
		protected:
			shared_ptr<DirectUI::Control::UIElement> m_Target;
			shared_ptr<DependencyPropertyBase> m_TargetDP;
		};

		template<typename T>
		class __declspec(dllexport) Binding : public BindingBase
		{
		public:
			shared_ptr<IValueConverter<T,T>> Converter;
		};
	}
}



