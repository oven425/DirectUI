#pragma once
#include <wincodecsdk.h>

namespace DirectUI
{
	class __declspec(dllexport) CImageSource
	{
	public:
		CImageSource();
		~CImageSource() {};
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


