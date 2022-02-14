#pragma once
class Thinckness
{
public:
	Thinckness(double data)
		: Left(data), Top(data), Right(data), Bottom(data)
	{}
	Thinckness(double data1, double data2)
		: Left(data1), Top(data2), Right(data1), Bottom(data2)
	{}
	double Left = 0;
	double Top = 0;
	double Right = 0;
	double Bottom = 0;
	//Thinckness operator+(int data) 
	//{
	//	return Thinckness();
	//}
};

