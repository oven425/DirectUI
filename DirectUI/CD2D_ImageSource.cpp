#include "pch.h"
#include "CD2D_ImageSource.h"
using namespace DirectUI;
IWICImagingFactory* CD2D_ImageSource::m_pIWICFactory = NULL;

CD2D_ImageSource::CD2D_ImageSource()
{
	if (CD2D_ImageSource::m_pIWICFactory == NULL)
	{
		::CoInitialize(NULL);
		HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&CD2D_ImageSource::m_pIWICFactory));
		hr = S_OK;
	}
}

CD2D_ImageSource::CD2D_ImageSource(const wchar_t* data)
	: CD2D_ImageSource()
{
	this->Open(data);
}

void CD2D_ImageSource::Open(const wchar_t* data)
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
	if (pIDecoderFrame != NULL)
	{
		pIDecoderFrame->Release();
	}
	if (pIDecoder != NULL)
	{
		pIDecoder->Release();
	}
}