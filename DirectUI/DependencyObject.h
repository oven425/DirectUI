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
		void SetValue(char data);
		void SetValue(unsigned char data);
		void SetValue(short data);
		void SetValue(unsigned short data);
		template <typename T>
		void SetValue(shared_ptr<DependencyProperty1<T>> dp, int data)
		{

		}
		void SetValue(unsigned int data);
		void SetValue(__int64 data);
		void SetValue(unsigned __int64 data);
		void SetValue(string data);
		void SetValue(wstring data);
		void SetValue(shared_ptr<void> data);
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
					dp->DependencyChangeHandler(*this->shared_from_this());
				}
			}
		}
		template <typename T>
		T GetValue(shared_ptr<DependencyProperty> dp)
		{
			if (dp)
			{
				auto ff = this->m_Save1.find(dp);
				if (ff != this->m_Save1.end())
				{
					return std::get<T>(ff->second);
				}
			}
			
			return T{};
		}

	protected:
		map<shared_ptr<DependencyProperty>, std::variant<char, unsigned char, short, unsigned short, int, unsigned int, __int64, unsigned __int64, float, double, string, wstring, shared_ptr<void>>> m_Save1;
	};
}


