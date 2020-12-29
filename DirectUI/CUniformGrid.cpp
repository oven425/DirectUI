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

void CUniformGrid::CheckRowCol(double width, double height)
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

void CUniformGrid::Measure(float width, float height)
{
	::CControl::Measure(width, height);
	this->CheckRowCol(this->DesiredSize.width, this->DesiredSize.height);
	for (auto oo : this->m_Childs)
	{
		oo->Measure(this->m_CellWidth - oo->Margin.GetLeft()-oo->Margin.GetRight(), this->m_CellHeight - oo->Margin.GetTop() - oo->Margin.GetBottom());
	}
}

void CUniformGrid::Arrange(float x, float y, float width, float height)
{
	::CControl::Arrange(x, y, width, height);

	int index = 0;
	for (int row = 0; row < this->m_CellRows; row++)
	{
		for (int col = 0; col < this->m_CellColums; col++)
		{
			index = row * this->m_CellColums + col;
			if (index < this->m_Childs.size())
			{
				this->m_Childs[index]->Arrange(col * this->m_CellWidth, row * this->m_CellHeight, this->m_CellWidth, this->m_CellHeight);

				//double x = col * this->m_CellWidth+ this->m_Childs[index]->Margin.GetLeft();
				//double y = row * this->m_CellHeight + this->m_Childs[index]->Margin.GetTop();
				//double w = this->m_CellWidth - this->m_Childs[index]->Margin.GetRight();
				//double h = this->m_CellHeight - this->m_Childs[index]->Margin.GetBottom();
				//if (this->m_Childs[index]->DesiredSize.width != this->m_CellWidth)
				//{
				//	switch (this->m_Childs[index]->GetHorizontalAlignment())
				//	{
				//	case HorizontalAlignments::Stretch:
				//	case HorizontalAlignments::Center:
				//	{
				//		x = x + (w - this->m_Childs[index]->DesiredSize.width) / 2;
				//	}
				//	break;
				//	case HorizontalAlignments::Right:
				//	{
				//		x = x + (w - this->m_Childs[index]->DesiredSize.width);
				//	}
				//	break;
				//	}
				//	w = this->m_Childs[index]->DesiredSize.width;
				//}
				//if (this->m_Childs[index]->DesiredSize.width != this->m_CellHeight)
				//{
				//	switch (this->m_Childs[index]->GetVerticalAlignment())
				//	{
				//	case VerticalAlignments::Stretch:
				//	case VerticalAlignments::Center:
				//	{
				//		y = y + (h - this->m_Childs[index]->DesiredSize.height) / 2;
				//	}
				//	break;
				//	case VerticalAlignments::Bottom:
				//	{
				//		y = y + (h - this->m_Childs[index]->DesiredSize.height);
				//	}
				//	break;
				//	}
				//	h = this->m_Childs[index]->DesiredSize.height;
				//}
				//this->m_Childs[index]->Arrange(x, y, w, h);
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