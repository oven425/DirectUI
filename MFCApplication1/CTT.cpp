#include "pch.h"
#include "CTT.h"

void CTT::SetValue(shared_ptr<void> data)
{
	shared_ptr<void> old;
	bool hasold = false;
	try 
	{
		old = std::get<shared_ptr<void>>(test);
		hasold = true;
	}
	catch (const std::bad_variant_access&) 
	{
	}
	if (hasold == true && data != old)
	{
		CTTChangeArgs<shared_ptr<void>> args;
	}
	test = data;
}

void CTT::SetValue(int data)
{
	bool hasold = false;
	int old = 0;
	try
	{
		old = std::get<int>(test);
	}
	catch (const std::bad_variant_access&)
	{
	}
	if (hasold == true && data != old)
	{
		CTTChangeArgs<int> args;
		args.NewValue = data;
		args.OldValue = old;
	}
	test = data;
}

void CTT::SetValue(float data)
{
	if (test.index() > 0)
	{
		float aa = std::get<float>(test);
		if (aa != data)
		{

		}
	}
	else
	{
		test = data;
	}
}

void CTT::SetValue(double data)
{
	if (test.index() > 0)
	{
		double aa = std::get<double>(test);
		if (aa != data)
		{

		}
	}
	else
	{
		test = data;
	}
}


