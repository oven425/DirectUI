#pragma once
#include "CD2D_Brush.h"
#include <memory>
using namespace std;
namespace DirectUI
{
namespace Control
{
	class __declspec(dllexport) CControl
	{
	protected:
		virtual void OnSize(int width, int height) {}
		virtual void OnRender() {}
	public:
		unique_ptr<CD2D_Brush> Background;
	};

}
}
	



