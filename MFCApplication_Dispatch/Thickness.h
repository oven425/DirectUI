#pragma once
class Thickness
{
public:
	Thickness() {}
	Thickness(double left_right, double top_bottom);
	Thickness(double left, double right, double top, double bottom);
	void SetLeft(double data);
	void SetTop(double data);
	void SetRight(double data);
	void SetBottom(double data);
	double GetLeft(void);
	double GetTop(void);
	double GetRight(void);
	double GetBottom(void);
protected:
	double m_Left = 0;
	double m_Top = 0;
	double m_Right = 0;
	double m_Bottom = 0;
};

