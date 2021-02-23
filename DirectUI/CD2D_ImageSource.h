#pragma once
#include <wincodecsdk.h>

namespace DirectUI
{
	namespace Direct2D
	{
		class __declspec(dllexport) CD2D_ImageSource
		{
		public:
			CD2D_ImageSource();
			CD2D_ImageSource(const wchar_t* data);
			~CD2D_ImageSource() {};
			void Open(const wchar_t* data);
			virtual operator IWICFormatConverter*() { return m_pConvertedSourceBitmap; }

		private:
			IWICFormatConverter* m_pConvertedSourceBitmap = NULL;
			static IWICImagingFactory* m_pIWICFactory;

		};
	}
}


