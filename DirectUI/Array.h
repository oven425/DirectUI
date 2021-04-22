#pragma once
#include <iterator>
using namespace std;

namespace IO
{
	template<typename T>
	class Array
	{
	public:
		void Fill(T data)
		{
			::memset(this->m_pBuf, data, this->m_Length);
		}

		//constexpr iterator begin()
		//{
		//	return iterator(this->m_pBuf, 0);
		//}
		void Clear()
		{
			::memset(this->m_pBuf, T{}, this->m_Length);
		}
		Array(int length)
		{
			this->m_Length = length;
			this->m_pBuf = new T[length];
			this->Clear();
		}
		~Array()
		{
			if (this->m_pBuf != nullptr)
			{
				delete[] this->m_pBuf;
				this->m_pBuf = nullptr;
			}
		}
	private:
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
			explicit iterator(long _num = 0) : num(_num) {}
			iterator& operator++() { num = TO >= FROM ? num + 1 : num - 1; return *this; }
			iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
			bool operator==(iterator other) const { return num == other.num; }
			bool operator!=(iterator other) const { return !(*this == other); }
			long operator*() const { return num; }
		};
		iterator begin() { return iterator(FROM); }
		iterator end() { return iterator(TO >= FROM ? TO + 1 : TO - 1); }
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


