#pragma once
#include <memory>
using namespace std;

class InnerTest
{
public:
	void Test();
};

class Test:public shared_ptr<InnerTest>
{
public:
	
};

