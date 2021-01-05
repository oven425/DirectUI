#pragma once
#include <wincodecsdk.h>

namespace DirectUI
{
	class __declspec(dllexport) CD2D_ImageSource
	{
	public:
		CD2D_ImageSource();
		~CD2D_ImageSource() {};
		void Open(const wchar_t* data);
		virtual operator IWICFormatConverter*() { return m_pConvertedSourceBitmap; }
		UINT GetWidth() { return this->m_Width; }
		UINT GetHeight() { return this->m_Height; }
	private:
		IWICFormatConverter* m_pConvertedSourceBitmap = NULL;
		static IWICImagingFactory* m_pIWICFactory;
		UINT m_Width = 0;
		UINT m_Height = 0;
	};
}


