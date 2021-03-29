#pragma once
#include <memory>
#include <variant>
using namespace std;

template<class T>
struct CTTChangeArgs
{
	T OldValue;
	T NewValue;
};

class CTT
{
public:

	void SetValue(shared_ptr<void> data);
	void SetValue(int data);
	void SetValue(float data);
	void SetValue(double data);

	template<typename T>
	T GetValue()
	{
		if (test.index() > 0)
		{
			return std::get<T>(test);
		}
		return T{};
	}
protected:
	std::variant<int, float, double, shared_ptr<void>> test;
};

