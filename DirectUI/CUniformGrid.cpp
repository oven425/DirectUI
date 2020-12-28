#include "pch.h"
#include <math.h>
#include "CUniformGrid.h"
using namespace DirectUI;
using namespace Control;

void CUniformGrid::OnRender(ID2D1HwndRenderTarget* pRT)
{
	::CControl::OnRender(pRT);
	for (auto oo : this->m_Childs)
	{
		oo->OnRender(pRT);
	}
}

void CUniformGrid::Measure(double width, double height)
{
	::CControl::Measure(width, height);
	for (auto oo : this->m_Childs)
	{
		oo->Measure(width, height);
	}
}

void CUniformGrid::Arrange(double x, double y, double width, double height)
{
	::CControl::Arrange(x, y, width, height);
	int maxcount = this->m_Childs.size();
	int rows = 0;
	int cols = 0;
	cols = rows = sqrt(maxcount);
	if (this->m_Columns > 0 && this->m_Rows > 0)
	{
		rows = this->m_Rows;
		cols = this->m_Columns;
		maxcount = rows * cols;
		if (maxcount > this->m_Childs.size())
		{
			maxcount = this->m_Childs.size();
		}
	}
	else if (this->m_Columns > 0)
	{
		cols = this->m_Columns;
	}
	else if (this->m_Rows > 0)
	{
		rows = this->m_Rows;
	}
	int index = 0;
	double w = width / cols;
	double h = height / rows;
	
	for (int row = 0; row < rows; row++)
	{
			for (int col = 0; col < cols; col++)
		{
			index = row * cols + col;
			if (index < this->m_Childs.size())
			{
				this->m_Childs[index]->Arrange(col*w, row*h, w, h);
			}
		}
	}
}

void CUniformGrid::OnSize(double width, double height, double dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
	for (auto oo : this->m_Childs)
	{
		oo->OnSize(width, height, dpiscale);
	}
}

void CUniformGrid::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
}

void CUniformGrid::SetRows(int data)
{
	this->m_Rows = data;
}
void CUniformGrid::SetColums(int data)
{
	this->m_Columns = data;
}