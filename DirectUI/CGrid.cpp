#include "pch.h"
#include "CGrid.h"
using namespace DirectUI;
using namespace Control;

//shared_ptr<DependencyProperty> CGrid::RowProperty;
//shared_ptr<DependencyProperty> CGrid::RowSpanProperty;
//shared_ptr<DependencyProperty> CGrid::ColumnProperty;
//shared_ptr<DependencyProperty> CGrid::ColumnSpanProperty;

CGrid::CGrid()
{
	//if (!RowProperty)
	//{
	//	RowProperty = DependencyProperty::Register(std::bind(PropertyChange, std::placeholders::_1));
	//}
	//if (!RowSpanProperty)
	//{
	//	RowSpanProperty = DependencyProperty::Register(std::bind(PropertyChange, std::placeholders::_1));
	//}
	//if (!ColumnProperty)
	//{
	//	ColumnProperty = DependencyProperty::Register(std::bind(PropertyChange, std::placeholders::_1));
	//}
	//if (!ColumnSpanProperty)
	//{
	//	ColumnSpanProperty = DependencyProperty::Register(std::bind(PropertyChange, std::placeholders::_1));
	//}
}

void CGrid::PropertyChange(const DependencyObject& sender)
{
	CControl& aa = (CControl&)sender;

}

void CGrid::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);

	::CControl::OnRender(pRT);
}

void CGrid::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	CDirectUI_Size sz = data + *this->Margin;
	vector<CDirectUI_Size> size_col;
	vector<CDirectUI_Size> size_row;
	for (auto oo : this->m_ColumnDefinitions)
	{

	}



	this->DesiredSize = sz;
}

void CGrid::Arrange(const CDirectUI_Rect& data)
{
	::CControl::Arrange(data);
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

//void CGrid::SetRow(shared_ptr<CControl> element, int data)
//{
//	element->SetValue(RowProperty, data);
//}
//
//void CGrid::SetRowSpan(shared_ptr<CControl> element, int data)
//{
//	element->SetValue(RowSpanProperty, data);
//}
//
//void CGrid::SetColumn(shared_ptr<CControl> element, int data)
//{
//	element->SetValue(ColumnProperty, data);
//}
//
//void CGrid::SetColumnSpan(shared_ptr<CControl> element, int data)
//{
//	element->SetValue(ColumnSpanProperty, data);
//}
//
//int CGrid::GetRow(shared_ptr<CControl> element)
//{
//	return element->GetValue<int>(RowProperty);
//}
//
//int CGrid::GetRowSpan(shared_ptr<CControl> element)
//{
//	return element->GetValue<int>(RowSpanProperty);
//}
//
//int CGrid::GetColumn(shared_ptr<CControl> element)
//{
//	return element->GetValue<int>(ColumnProperty);
//}
//
//int CGrid::GetColumnSpan(shared_ptr<CControl> element)
//{
//	return element->GetValue<int>(ColumnSpanProperty);
//}