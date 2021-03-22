#pragma once
#include <map>
#include <variant>
using namespace std;

#include "DependencyProperty.h"

namespace DirectUI
{
	class DependencyObject:public enable_shared_from_this<DependencyObject>
	{
	public:
		template <typename T>
		void SetValue(shared_ptr<DependencyProperty> dp, T data)
		{
			if (dp)
			{
				auto ff = this->m_Save1.find(dp);
				if (ff != this->m_Save1.end())
				{
					this->m_Save1[dp] = data;
					dp->DependencyChangeHandler(*this->shared_from_this());
				}
				else
				{
					this->m_Save1[dp] = data;
				}
			}
		}
		template <typename T>
		T GetValue(shared_ptr<DependencyProperty> dp)
		{
			
			auto ff = this->m_Save1.find(dp);
			if (ff != this->m_Save1.end())
			{
				
				return std::get<T>(ff->second);
			}
			return T{};
			//return make_shared<T>();
		}
		//template <typename T>
		//shared_ptr<T> GetValue(shared_ptr<DependencyProperty> dp)
		//{
		//	auto ff = this->m_Save.find(dp);
		//	if (ff != this->m_Save.end())
		//	{
		//		return static_pointer_cast<T>(ff->second);
		//	}
		//	return nullptr;
		//	return make_shared<T>();
		//}
	protected:
		map<shared_ptr<DependencyProperty>, std::variant<char, unsigned char, short, unsigned short, int, unsigned int, __int64, unsigned __int64, float, double, string, wstring, shared_ptr<void>>> m_Save1;
		//map<shared_ptr<DependencyProperty>, shared_ptr<void>> m_Save;
	};
}


