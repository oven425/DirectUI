#pragma once
#include <map>
using namespace std;

namespace DirectUI
{
	template <class T1, class T2>
	class __declspec(dllexport) CDependencyObject
	{
	public:
		void SetValue(T1 key, T2 value)
		{
			this->m_Save[key] = value;
		}

		T2 GetValue(T1 key)
		{
			T2 value{};
			auto find = this->m_Save.find(key);
			if (find != this->m_Save.end())
			{
				return find->second;
			}
			return value;
		}

	protected:
		map<T1, T2> m_Save;
	};
}


