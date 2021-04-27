#pragma once
#include <map>
#include <variant>
using namespace std;
#include "Binding.h"
#include "DispatcherObject.h"
using namespace DirectUI;
using namespace Data;
using namespace Threading;

#include "DependencyProperty.h"

namespace DirectUI
{
	namespace Extension
	{
		template<class T>
		struct is_shared_ptr : std::false_type {};

		template<class T>
		struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};
	}
}

namespace DirectUI
{
	

	class DependencyObject:public DispatcherObject, public enable_shared_from_this<DependencyObject>
	{
	public:
		template<typename T>
		inline typename std::enable_if<Extension::is_shared_ptr<T>::value, void>::type
			SetValue(shared_ptr<DependencyProperty<T>> dp, T data)
		{
			if (!dp)
			{
				return;
			}
			T old;
			bool hasold = false;
			auto find = this->m_Save.find(dp);
			if (find != this->m_Save.end())
			{
				try
				{
					old = this->GetValue<T>(dp);
					if (old)
					{
						hasold = true;
					}
				}
				catch (const std::bad_variant_access&)
				{
				}
			}
			if (hasold == true && data != old)
			{
				auto args = DependencyPropertyChangeArgs<T>();
				args.OldValue = old;
				args.NewValue = data;
				//if (dp->DependencyChangeHandler)
				//{
				//	dp->DependencyChangeHandler(*this, args);
				//}
				dp->DependencyChangeHandler.Fire(*this, args);
			}
			m_Save[dp] = data;
		}

		template<typename T>
		inline typename std::enable_if<!Extension::is_shared_ptr<T>::value&&std::is_arithmetic<T>::value, void>::type
			SetValue(shared_ptr<DependencyProperty<T>> dp, T data)
		{
			if (!dp)
			{
				return;
			}
			T old;
			bool hasold = false;
			auto find = this->m_Save.find(dp);
			if (find != this->m_Save.end())
			{
				try
				{
					old = std::get<T>(find->second);
					hasold = true;
				}
				catch (const std::bad_variant_access&)
				{
				}
			}
			if (hasold == true && data != old)
			{
				auto args = DependencyPropertyChangeArgs<T>();
				args.OldValue = old;
				args.NewValue = data;
				//if (dp->DependencyChangeHandler)
				//{
				//	dp->DependencyChangeHandler(*this, args);
				//}
				dp->DependencyChangeHandler.Fire(*this, args);
			}

			m_Save[dp] = data;
		}

		template<typename T>
		inline typename std::enable_if<!Extension::is_shared_ptr<T>::value&&std::is_arithmetic<T>::value, T>::type
			GetValue(shared_ptr<DependencyProperty<T>> dp)
		{
			if (dp)
			{
				auto find = this->m_Save.find(dp);
				if (find != this->m_Save.end())
				{
					try
					{
						return std::get<T>(find->second);
					}
					catch (const std::bad_variant_access& err)
					{
						//::OutputDebugStringA("");
					}
				}
			}
			return T{};
		}

		template<typename T>
		inline typename std::enable_if<Extension::is_shared_ptr<T>::value, T>::type
			GetValue(shared_ptr<DependencyProperty<T>> dp)
		{
			if (dp)
			{
				auto find = this->m_Save.find(dp);
				if (find != this->m_Save.end())
				{
					try
					{
						auto aa = std::get<shared_ptr<void>>(find->second);
						const auto _Ptr = static_cast<typename T::element_type *>(aa.get());
						return (T(aa, _Ptr));
					}
					catch (const std::bad_variant_access& err)
					{
						//::OutputDebugStringA("");
					}
				}
				return (*dp).m_Default;
			}
			return T{};
		}


		//template<typename T>
		//void SetValue(shared_ptr<DependencyProperty<T>> dp, shared_ptr<T> data)
		//{
		//	if (!dp)
		//	{
		//		return;
		//	}
		//	shared_ptr<void> old;
		//	bool hasold = false;
		//	auto find = this->m_Save.find(dp);
		//	if (find != this->m_Save.end())
		//	{
		//		try
		//		{
		//			old = std::get<shared_ptr<void>>(find->second);
		//			if (old)
		//			{
		//				hasold = true;
		//			}
		//		}
		//		catch (const std::bad_variant_access&)
		//		{
		//		}
		//	}
		//	if (hasold == true && data != old)
		//	{
		//		auto args = DependencyPropertyChangeArgs<T>();
		//		args.OldValue = *static_pointer_cast<T>(old);
		//		args.NewValue = *data;
		//		if (dp->DependencyChangeHandler)
		//		{
		//			dp->DependencyChangeHandler(*this, args);
		//		}
		//	}
		//	m_Save[dp] = data;
		//}

		//template<typename T>
		//void SetValue(shared_ptr<DependencyProperty<T>> dp, T data)
		//{
		//	if (!dp)
		//	{
		//		return;
		//	}
		//	T old;
		//	bool hasold = false;
		//	auto find = this->m_Save.find(dp);
		//	if (find != this->m_Save.end())
		//	{
		//		try
		//		{
		//			old = std::get<T>(find->second);
		//			hasold = true;
		//		}
		//		catch (const std::bad_variant_access&)
		//		{
		//		}
		//	}
		//	if (hasold == true && data != old)
		//	{
		//		auto args = DependencyPropertyChangeArgs<T>();
		//		args.OldValue = old;
		//		args.NewValue = data;
		//		if (dp->DependencyChangeHandler)
		//		{
		//			dp->DependencyChangeHandler(*this, args);
		//		}
		//	}

		//	m_Save[dp] = data;
		//}
		
		//template<typename T, typename T1>
		//T GetValue(shared_ptr<DependencyProperty<T1>> dp)
		//{
		//	if (dp)
		//	{
		//		auto find = this->m_Save.find(dp);
		//		if (find != this->m_Save.end())
		//		{
		//			try
		//			{
		//				return std::get<T>(find->second);
		//			}
		//			catch (const std::bad_variant_access& err)
		//			{
		//				//::OutputDebugStringA("");
		//			}
		//		}
		//	}

		//	return T{};
		//}

		template<typename T>
		void ClearValue(shared_ptr<DependencyProperty<T>> dp)
		{
			if (dp)
			{
				auto find = this->m_Save.find(dp);
				if (find != this->m_Save.end())
				{
					try
					{
						this->m_Save.erase(find);
					}
					catch (const std::bad_variant_access& err)
					{
						//::OutputDebugStringA("");
					}
				}
			}
		}

		template<typename T>
		void SetBinding(shared_ptr<DependencyProperty<T>> dp, shared_ptr<BindingBase> data)
		{
			this->ClearValue(dp);
			this->m_SaveBinding[dp] = data;
		}

		template<typename T>
		void ClearBinding(shared_ptr<DependencyProperty<T>> dp)
		{
			if (dp)
			{
				auto find = this->m_SaveBinding.find(dp);
				if (find != this->m_SaveBinding.end())
				{
					try
					{
						this->m_SaveBinding.erase(find);
					}
					catch (const std::bad_variant_access& err)
					{
						//::OutputDebugStringA("");
					}
				}
			}
		}

	protected:
		map<shared_ptr<DependencyPropertyBase>, std::variant<bool, char, unsigned char, short, unsigned short, int, unsigned int, __int64, unsigned __int64, float, double, string, wstring, shared_ptr<void>>> m_Save;
		map<shared_ptr<DependencyPropertyBase>, shared_ptr<BindingBase>> m_SaveBinding;
	};
}


