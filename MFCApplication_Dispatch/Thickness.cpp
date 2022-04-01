#include "pch.h"
#include "Thickness.h"
Thickness::Thickness(double left_right, double top_bottom)
	: m_Left(left_right)
	, m_Top(top_bottom)
	, m_Right(left_right)
	, m_Bottom(top_bottom)
{
	
}
Thickness::Thickness(double left, double right, double top, double bottom)
	: m_Left(left)
	, m_Top(top)
	, m_Right(right)
	, m_Bottom(bottom)
{

}
void Thickness::SetLeft(double data)
{
	this->m_Left = data;
}

void Thickness::SetTop(double data)
{
	this->m_Top = data;
}

void Thickness::SetRight(double data)
{
	this->m_Right = data;
}

void Thickness::SetBottom(double data)
{
	this->m_Bottom = data;
}

double Thickness::GetLeft(void)
{
	return this->m_Left;
}

double Thickness::GetTop(void)
{
	return this->m_Top;
}

double Thickness::GetRight(void)
{
	return this->m_Right;
}

double Thickness::GetBottom(void)
{
	return this->m_Bottom;
}