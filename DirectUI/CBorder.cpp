#include "pch.h"
#include "CBorder.h"
using namespace DirectUI;
using namespace Control;

void CBorder::Measure(int width, int height)
{
	this->DesiredSize.cx = width;
	this->DesiredSize.cy = height;
}

void CBorder::OnSize(int width, int height)
{

}

void CBorder::OnRender()
{

}
