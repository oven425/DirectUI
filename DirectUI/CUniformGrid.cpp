#include "pch.h"
#include <math.h>
#include "CUniformGrid.h"
using namespace DirectUI;
using namespace Control;

void CUniformGrid::OnRender(ID2D1RenderTarget* pRT)
{
	::CControl::OnRender(pRT);
	for (auto oo : this->m_Childs)
	{
		oo->OnRender(pRT);
	}
}

void CUniformGrid::CheckRowCol(float width, float height)
{
	this->m_CellCount = this->m_Childs.size();
	this->m_CellRows = 0;
	this->m_CellColums = 0;
	this->m_CellColums = this->m_CellRows = ceil(sqrt(this->m_CellCount));
	if (this->m_Columns > 0 && this->m_Rows > 0)
	{
		this->m_CellRows = this->m_Rows;
		this->m_CellColums = this->m_Columns;
		this->m_CellCount = this->m_CellRows * this->m_CellColums;
		if (this->m_CellCount > this->m_Childs.size())
		{
			this->m_CellCount = this->m_Childs.size();
		}
	}
	else if (this->m_Columns > 0)
	{
		this->m_CellColums = this->m_Columns;
		double dd = (double)this->m_CellCount / this->m_CellColums;
		this->m_CellRows = ceil(dd);
	}
	else if (this->m_Rows > 0)
	{
		this->m_CellRows = this->m_Rows;
		double dd = (double)this->m_CellCount / this->m_CellRows;
		this->m_CellColums = ceil(dd);
	}
	int index = 0;
	this->m_CellWidth = width / this->m_CellColums;
	this->m_CellHeight = height / this->m_CellRows;
}

void CUniformGrid::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	::CControl::Measure(width, height, pRT);
	this->CheckRowCol(this->DesiredSize.width, this->DesiredSize.height);
	for (auto oo : this->m_Childs)
	{
		oo->Measure(this->m_CellWidth, this->m_CellHeight, pRT);
	}

	vector<float> widths(this->m_CellColums,0);
	vector<float> heights(this->m_CellRows, 0);
	int index = 0;
	for (int row = 0; row < this->m_CellRows; row++)
	{
		for (int col = 0; col < this->m_CellColums; col++)
		{
			index = row * this->m_CellColums + col;
			if (index < this->m_Childs.size())
			{
				if (widths[col] < this->m_Childs[index]->DesiredSize.width)
				{
					widths[col] = this->m_Childs[index]->DesiredSize.width;
				}
				if (heights[row] < this->m_Childs[index]->DesiredSize.height)
				{
					heights[row] = this->m_Childs[index]->DesiredSize.height;
				}
			}
		}
	}
	auto width1 = *std::max_element(widths.begin(), widths.end());
	auto height1 = *std::max_element(heights.begin(), heights.end());
	this->DesiredSize.width = width1 * this->m_CellColums;
	this->DesiredSize.height = height1 * this->m_CellRows;
}

void CUniformGrid::Arrange(float x, float y, float width, float height)
{
	::CControl::Arrange(x, y, width, height);

	this->CheckRowCol(this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	int index = 0;
	float cellwidth = this->m_CellWidth;
	for (int row = 0; row < this->m_CellRows; row++)
	{
		for (int col = 0; col < this->m_CellColums; col++)
		{
			index = row * this->m_CellColums + col;
			
			if (index < this->m_Childs.size())
			{
				float cellwidth = this->m_CellWidth;
				float cellheight = this->m_CellHeight;
				float x1 = this->m_ActualRect.GetX() + col * cellwidth;
				float y1 = this->m_ActualRect.GetY() + row * cellheight;
				this->m_Childs[index]->Arrange(x1,y1, cellwidth, cellheight);
			}
		}
	}
}

void CUniformGrid::OnSize(float width, float height, float dpiscale)
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