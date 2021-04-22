#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <array>
using namespace std;

#include "Array.h"

namespace IO
{
	class File
	{
	public:
		static void ReadAllBytes(wstring filename)
		{
			auto range = Range<15, 25>();
			auto itr = std::find(range.begin(), range.end(), 18);
			std::cout << *itr << '\n'; // 18

			// Range::iterator also satisfies range-based for requirements
			for (auto l : Range<3, 5>()) {
				std::cout << l << ' '; // 3 4 5
			}
			std::cout << '\n';

			//int numbers[] = { 10,20,30,40,50 };
			//MyIterator from(numbers);
			//MyIterator until(numbers + 5);
			//for (MyIterator it = from; it != until; it++)
			//	std::cout << *it << ' ';
			//for (auto oo : from)
			//{

			//}
			//std::cout << '\n';


			ifstream  file;
			file.open(filename, ios::out | ios::in);
			int size = 100;
			array<unsigned char, 100> buf;
			for (auto oo : buf)
			{

			}
			//buf.Fill(0);
			file.close();
		}
	};

}

