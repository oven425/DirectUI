#include "pch.h"
#include "CBorder.h"
using namespace DirectUI;
using namespace Control;

CBorder::CBorder()
{

}

CBorder::CBorder(const CBorder& data)
{

}

CBorder::CBorder(const CBorder&& data)
{

}

void CBorder::Measure(int width, int height)
{
	this->DesiredSize.cx = width;
	this->DesiredSize.cy = height;
}

void CBorder::OnSize(int width, int height)
{

}

void CBorder::OnRender(ID2D1HwndRenderTarget* pRT)
{
	
}
