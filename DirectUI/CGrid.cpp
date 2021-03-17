#include "pch.h"
#include "CGrid.h"
using namespace DirectUI;
using namespace Control;

void CGrid::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);

	::CControl::OnRender(pRT);
}

void CGrid::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	CDirectUI_Size sz = data + this->m_Margin;
	this->DesiredSize = sz;
}

void CGrid::Arrange(const CDirectUI_Rect& data)
{
	::CControl::Arrange(data);
}

void CGrid::AddCild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
}

void CGrid::SetRowDefinitions(vector<shared_ptr<CGridRowDefintion>> datas)
{
	this->m_RowDefinitions.clear();
	this->m_RowDefinitions = datas;
}

void CGrid::SetColumnDefinitions(vector<shared_ptr<CGridColumnDefinition>> datas)
{
	this->m_ColumnDefinitions.clear();
	this->m_ColumnDefinitions = datas;
}