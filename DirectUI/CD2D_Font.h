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
		~CD2D_Font();
		void SetFontName(const wstring& name);
		void SetFontSize(float data);
		static vector<wstring>& GetFontNmaes();
		float GetFontSize() { return this->m_FontSize; }
		wstring& GetFontName() { return this->m_FontName; }
		operator IDWriteTextFormat*();
		D2D1_SIZE_F GetTextSize(const wchar_t* data);
	protected:
		static IDWriteFactory* m_pDWriteFactory;
		static vector<wstring> m_FontNames;
		IDWriteTextFormat* m_pTextFormat = NULL;
		float m_FontSize = 12;
		wstring m_FontName = L"Arial";
		void CreateFont_();
	};
}


