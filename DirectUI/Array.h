#pragma once
#include <iterator>
#include <iostream>
#include <fstream>
using namespace std;

namespace IO
{
	template<typename T>
	class Array
	{
	public:
		class iterator :public std::iterator<std::input_iterator_tag, T*, T*, const T** ,T*>
		{
		public:
			explicit iterator(T* data, int index)
			{
				this->m_Data = data;
				this->m_Index = index;
			}
			iterator& operator++()
			{
				//this->m_Data++;
				this->m_Index++;
				return *this;
			}
			iterator operator++(int) 
			{ 
				iterator tmp(*this); 
				operator++(); 
				return tmp; 
			}
			bool operator==(iterator other) const
			{
				return this->m_Index == other.m_Index;
				//return this->m_Data == other.m_Data;
			}
			bool operator!=(iterator other) const
			{
				return !(*this == other);
			}

			T operator*() const
			{
				return *(this->m_Data+this->m_Index);
			}
		protected:
			int m_Index = 0;
			int m_Length;
			T* m_Data;
		};
		Array(int length)
		{
			this->m_Length = length;
			this->m_pBuf = new T[length];
			::memset(this->m_pBuf, 0, sizeof(T)*this->m_Length);
			for (int i = 0; i < this->m_Length; i++)
			{
				*(this->m_pBuf + i) = i;
			}
		}
		~Array()
		{
			if (this->m_pBuf != nullptr)
			{
				delete[] this->m_pBuf;
				this->m_pBuf = nullptr;
			}
		}
		iterator begin()
		{
			return iterator(this->m_pBuf, 0);
		}
		iterator end()
		{
			return iterator((this->m_pBuf+this->m_Length-1), this->m_Length);
		}
		T operator[](int index)
		{
			return *(this->m_pBuf + index-1);
		}

	public:
		T* m_pBuf = nullptr;
		int m_Length = 0;
		int m_Pos = 0;
	};

	template<long FROM, long TO>
	class Range {
	public:
		// member typedefs provided through inheriting from std::iterator
		class iterator : public std::iterator<
			std::input_iterator_tag,   // iterator_category
			long,                      // value_type
			long,                      // difference_type
			const long*,               // pointer
			long                       // reference
		> {
			long num = FROM;
		public:
			explicit iterator(long _num = 0) 
				: num(_num) 
			{
			}
			iterator& operator++() 
			{ 
				num = TO >= FROM ? num + 1 : num - 1; 
				return *this; 
			}
			iterator operator++(int) 
			{ 
				iterator retval = *this; 
				++(*this); return retval; 
			}
			bool operator==(iterator other) const 
			{ 
				return num == other.num; 
			}
			bool operator!=(iterator other) const 
			{ 
				return !(*this == other); 
			}
			long operator*() const 
			{ 
				return num; 
			}
		};
		iterator begin() 
		{ 
			return iterator(FROM); 
		}
		iterator end() 
		{ 
			return iterator(TO >= FROM ? TO + 1 : TO - 1); 
		}
	};

	class MyIterator : public std::iterator<std::input_iterator_tag, int>
	{
		int* p;
	public:
		MyIterator(int* x) :p(x) {}
		MyIterator(const MyIterator& mit) : p(mit.p) {}
		MyIterator& operator++() { ++p; return *this; }
		MyIterator operator++(int) { MyIterator tmp(*this); operator++(); return tmp; }
		bool operator==(const MyIterator& rhs) const { return p == rhs.p; }
		bool operator!=(const MyIterator& rhs) const { return p != rhs.p; }
		int& operator*() { return *p; }
	};
}


