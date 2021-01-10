#pragma once
#include <dwrite.h>
#include <vector>
#include <memory>
using namespace std;

namespace DirectUI
{
	class __declspec(dllexport) CD2D_Font
	{
	public:
		CD2D_Font();
		static vector<wstring>& GetFontNmaes();
	protected:
		static IDWriteFactory* m_pDWriteFactory;
		static vector<wstring> m_FontNames;
	};
}


