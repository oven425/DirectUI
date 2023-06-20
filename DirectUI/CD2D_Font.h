#pragma once
#include <dwrite.h>
#include <vector>
#include <memory>
#include <string>
using namespace std;

namespace DirectUI
{
	namespace Direct2D
	{
		class __declspec(dllexport) CD2D_Font
		{
		public:
			CD2D_Font();
			~CD2D_Font();
			void SetFontName(const wstring& name);
			void SetFontSize(float data);
			void SetFontWeight(DWRITE_FONT_WEIGHT data = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD);
			void SetFontStyle(DWRITE_FONT_STYLE data = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_ITALIC);
			void SetUnderLine(bool data);
			void SetFontStretch(DWRITE_FONT_STRETCH data);
			void SetWrapping(DWRITE_WORD_WRAPPING data);
			void SetTriming(DWRITE_TRIMMING_GRANULARITY data);
			void SetAligment(DWRITE_TEXT_ALIGNMENT data);
			static vector<wstring>& GetFontNmaes();
			float GetFontSize() { return this->m_FontSize; }
			wstring& GetFontName() { return this->m_FontName; }
			operator IDWriteTextFormat*();
			operator IDWriteTextLayout*();
			D2D1_SIZE_F GetTextSize(const wchar_t* data, float width, float height);
		protected:
			void Release();
			static IDWriteFactory* m_pDWriteFactory;
			static vector<wstring> m_FontNames;
			IDWriteTextFormat* m_pTextFormat = NULL;
			IDWriteTextLayout* m_pTextLayout = NULL;
			IDWriteInlineObject* m_pTrimeObject = NULL;
			float m_FontSize = 12;
			wstring m_FontName = L"Arial";
			void CreateFont_();
			DWRITE_TEXT_ALIGNMENT m_Aligment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
			DWRITE_FONT_WEIGHT m_FontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
			DWRITE_FONT_STYLE m_FontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
			DWRITE_FONT_STRETCH m_FontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
			DWRITE_WORD_WRAPPING m_Wrapping = DWRITE_WORD_WRAPPING::DWRITE_WORD_WRAPPING_NO_WRAP;
			DWRITE_TRIMMING_GRANULARITY m_Triming = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_NONE;
			bool m_IsUnderLine = false;
		};
	}
}


