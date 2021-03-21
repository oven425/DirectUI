#pragma once
#include <map>
using namespace std;

#include "DependencyProperty.h"

namespace DirectUI
{
	class DependencyObject:public enable_shared_from_this<DependencyObject>
	{
	public:
		void SetValue(shared_ptr<DependencyProperty> dp, shared_ptr<void> data)
		{
				auto ff = this->m_Save.find(dp);
	//dp->DependencyChangeHandler(this);
	if (ff != this->m_Save.end())
	{
		this->m_Save[dp] = data;
		
	}
	else
	{
		this->m_Save[dp] = data;
	}
		}
		//template <typename T>
		//void SetValue(shared_ptr<DependencyProperty> dp, T data)
		//{
		//	auto ff = this->m_Save.find(dp);
		//	if (ff != this->m_Save.end())
		//	{
		//		this->m_Save[dp] = data;
		//		dp->DependencyChangeHandler();
		//	}
		//	else
		//	{
		//		this->m_Save[dp] = make_shared<T>(data);
		//	}
		//}
		template <typename T>
		shared_ptr<T> GetValue(shared_ptr<DependencyProperty> dp)
		{
			auto ff = this->m_Save.find(dp);
			if (ff != this->m_Save.end())
			{
				return static_pointer_cast<T>(ff->second);
			}
			return nullptr;
			return make_shared<T>();
		}
	protected:
		map<shared_ptr<DependencyProperty>, shared_ptr<void>> m_Save;
	};
}


