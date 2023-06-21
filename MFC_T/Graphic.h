#pragma once
#include <mutex>
#include <functional>
using namespace std;
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

class Graphic
{
public:
	static Graphic* Mount()
	{
		return nullptr;
	}
private:
	Graphic();
	static once_flag m_Once;
	static CComPtr<ID2D1Factory> m_GraphicsFactory;
};



