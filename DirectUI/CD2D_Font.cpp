#include "pch.h"
#include "CD2D_Font.h"
using namespace DirectUI;
IDWriteFactory* CD2D_Font::m_pDWriteFactory = NULL;
vector<wstring> CD2D_Font::m_FontNames;

CD2D_Font::CD2D_Font()
{
	if (CD2D_Font::m_pDWriteFactory == NULL)
	{
		HRESULT hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&CD2D_Font::m_pDWriteFactory)
		);

		IDWriteFontCollection* pFontCollection = NULL;

		// Get the system font collection.
		if (SUCCEEDED(hr))
		{
			hr = CD2D_Font::m_pDWriteFactory->GetSystemFontCollection(&pFontCollection);
		}
		UINT32 familyCount = 0;

		// Get the number of font families in the collection.
		if (SUCCEEDED(hr))
		{
			familyCount = pFontCollection->GetFontFamilyCount();
		}
		for (UINT32 i = 0; i < familyCount; ++i)
		{
			IDWriteFontFamily* pFontFamily = NULL;

			// Get the font family.
			if (SUCCEEDED(hr))
			{
				hr = pFontCollection->GetFontFamily(i, &pFontFamily);
			}
			IDWriteLocalizedStrings* pFamilyNames = NULL;

			// Get a list of localized strings for the family name.
			if (SUCCEEDED(hr))
			{
				hr = pFontFamily->GetFamilyNames(&pFamilyNames);
			}

			UINT32 index = 0;
			BOOL exists = false;

			wchar_t localeName[LOCALE_NAME_MAX_LENGTH];

			if (SUCCEEDED(hr))
			{
				// Get the default locale for this user.
				int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);

				// If the default locale is returned, find that locale name, otherwise use "en-us".
				if (defaultLocaleSuccess)
				{
					hr = pFamilyNames->FindLocaleName(localeName, &index, &exists);
				}
				if (SUCCEEDED(hr) && !exists) // if the above find did not find a match, retry with US English
				{
					hr = pFamilyNames->FindLocaleName(L"en-us", &index, &exists);
				}
			}

			// If the specified locale doesn't exist, select the first on the list.
			if (!exists)
				index = 0;

			UINT32 length = 0;

			// Get the string length.
			if (SUCCEEDED(hr))
			{
				hr = pFamilyNames->GetStringLength(index, &length);
			}

			// Allocate a string big enough to hold the name.
			//unique_ptr<wchar_t[]> name1 = make_unique<wchar_t[]>(length + 1);
			wchar_t* name = new wchar_t[length + 1];
			// Get the family name.
			if (SUCCEEDED(hr))
			{
				hr = pFamilyNames->GetString(index, name, length + 1);
			}
			m_FontNames.push_back(name);
		}
	}
}

CD2D_Font::~CD2D_Font()
{
	if (this->m_pTextFormat != NULL)
	{
		this->m_pTextFormat->Release();
		this->m_pTextFormat = NULL;
	}
}

vector<wstring>& CD2D_Font::GetFontNmaes()
{
	return CD2D_Font::m_FontNames;
}

void CD2D_Font::SetFontSize(float data)
{
	if (this->m_pTextFormat != NULL)
	{
		this->m_pTextFormat->Release();
		this->m_pTextFormat = NULL;
	}
	this->m_FontSize = data;
}

void CD2D_Font::SetFontName(const wstring& name)
{
	if (this->m_pTextFormat != NULL)
	{
		this->m_pTextFormat->Release();
		this->m_pTextFormat = NULL;
	}
	this->m_FontName = name;
}

void CD2D_Font::CreateFont_()
{
	if (this->m_pTextFormat != NULL)
	{
		this->m_pTextFormat->Release();
		this->m_pTextFormat = NULL;
	}

	HRESULT hr = CD2D_Font::m_pDWriteFactory->CreateTextFormat(
		this->m_FontName.c_str(),                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		this->m_FontSize,
		L"en-us",
		&this->m_pTextFormat
	);
	
}

D2D1_SIZE_F CD2D_Font::GetTextSize(const wchar_t* data)
{
	D2D1_SIZE_F sz = { 0 };
	HRESULT hr = S_OK;
	IDWriteTextLayout* pTextLayout = NULL;
	hr = m_pDWriteFactory->CreateTextLayout(data, wcslen(data), *this, 0.0f, 0.0f, &pTextLayout);
	if (SUCCEEDED(hr))
	{
		DWRITE_TEXT_METRICS textMetrics;
		hr = pTextLayout->GetMetrics(&textMetrics);
		sz.width = ceil(textMetrics.widthIncludingTrailingWhitespace)*textMetrics.lineCount;
		sz.height = ceil(textMetrics.height);
	}
	pTextLayout->Release();

	return sz;
}

CD2D_Font::operator IDWriteTextFormat*()
{
	if (this->m_pTextFormat == NULL)
	{
		this->CreateFont_();
	}
	return  this->m_pTextFormat;
}