#include "pch.h"
#include "Ellipse.h"
using namespace DirectUI;
using namespace Shapes;

void Ellipse::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{

}

void Ellipse::Arrange(const CDirectUI_Rect& data)
{

}

void Ellipse::OnRender(ID2D1RenderTarget* pRT)
{
	this->CreateRenderBuf(pRT, this->DesiredSize);
	

	Control::CControl::OnRender(pRT);
	
}