#pragma once
class Size
{
public:
	Size() {}
	Size(double width, double height)
		: m_Width(width)
		, m_Height(height)
	{

	}
	double GetWidth() { return this->m_Width; }
	double GetHeight() { return this->m_Height; }
	double SetWidht(double data) { this->m_Width = data; }
	double SetHeight(double data) { this->m_Height = data; }
protected:
	double m_Width = 0;
	double m_Height = 0;
};

