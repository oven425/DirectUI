#include "pch.h"
#include "RadioButton.h"
using namespace DirectUI;
using namespace Control;

//DependencyProperty RadioButton::IsCheckedProperty;
//DependencyProperty RadioButton::GroupNameProperty;


void RadioButton::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);
}

void RadioButton::Arrange(const CDirectUI_Rect& data)
{
	::CContentControl::Arrange(data);
}

void RadioButton::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 12;
	::CContentControl::Measure(data, pRT);
}

void RadioButton::SetContent(const wchar_t* data)
{
	if (this->m_Child)
	{

	}

}