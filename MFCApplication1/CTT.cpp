#include "pch.h"
#include "CTT.h"

//void CTT_Object::SetValue(shared_ptr<CTT_Propoerty> dp, shared_ptr<void> data)
//{
//	shared_ptr<void> old;
//	bool hasold = false;
//	auto find = this->test.find(dp);
//	if (find != this->test.end())
//	{
//		try
//		{
//			old = std::get<shared_ptr<void>>(find->second);
//			hasold = true;
//		}
//		catch (const std::bad_variant_access&)
//		{
//		}
//	}
//	
//	if (hasold == true && data != old)
//	{
//		CTTChangeArgs<shared_ptr<void>> args;
//	}
//	test[dp] = data;
//}

//void CTT_Object::SetValue(shared_ptr<CTT_Propoerty> dp, int data)
//{
//	//bool hasold = false;
//	//int old = 0;
//	//try
//	//{
//	//	old = std::get<int>(test);
//	//}
//	//catch (const std::bad_variant_access&)
//	//{
//	//}
//	//if (hasold == true && data != old)
//	//{
//	//	CTTChangeArgs<int> args;
//	//	args.NewValue = data;
//	//	args.OldValue = old;
//	//	if (this->Handler)
//	//	{
//	//		this->Handler(this, args);
//	//	}
//	//}
//	//test = data;
//}

//void CTT_Object::SetValue(shared_ptr<CTT_Propoerty> dp, float data)
//{
//
//}
//
//void CTT_Object::SetValue(shared_ptr<CTT_Propoerty> dp, double data)
//{
//}


