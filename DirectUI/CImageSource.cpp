#include "pch.h"
#include "CImageSource.h"
using namespace DirectUI;
IWICImagingFactory* CImageSource::m_pIWICFactory = NULL;

CImageSource::CImageSource()
{
	if (CImageSource::m_pIWICFactory == NULL)
	{
		::CoInitialize(NULL);
		HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&CImageSource::m_pIWICFactory));
		hr = S_OK;
	}
}

void CImageSource::Open(const wchar_t* data)
{
	IWICBitmapDecoder *pIDecoder = NULL;
	IWICBitmapFrameDecode *pIDecoderFrame = NULL;

	HRESULT hr = m_pIWICFactory->CreateDecoderFromFilename(
		data,                  // Image to be decoded
		NULL,                           // Do not prefer a particular vendor
		GENERIC_READ,                   // Desired read access to the file
		WICDecodeMetadataCacheOnDemand, // Cache metadata when needed
		&pIDecoder                      // Pointer to the decoder
	);

	if (SUCCEEDED(hr))
	{
		hr = pIDecoder->GetFrame(0, &pIDecoderFrame);
	}

	pIDecoderFrame->GetSize(&this->m_Width, &this->m_Height);
	double x = 0;
	double y = 0;
	pIDecoderFrame->GetResolution(&x, &y);
	if (this->m_pConvertedSourceBitmap != NULL)
	{
		this->m_pConvertedSourceBitmap->Release();
		this->m_pConvertedSourceBitmap = NULL;
	}
	
	m_pIWICFactory->CreateFormatConverter(&m_pConvertedSourceBitmap);

	if (SUCCEEDED(hr))
	{
		hr = m_pConvertedSourceBitmap->Initialize(
			pIDecoderFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}
	pIDecoderFrame->Release();
	pIDecoder->Release();
}