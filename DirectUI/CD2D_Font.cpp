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
	this->Release();
}

vector<wstring>& CD2D_Font::GetFontNmaes()
{
	return CD2D_Font::m_FontNames;
}

void CD2D_Font::SetAligment(DWRITE_TEXT_ALIGNMENT data)
{
	this->Release();
	this->m_Aligment = data;
}

void CD2D_Font::SetTriming(DWRITE_TRIMMING_GRANULARITY data)
{
	this->Release();
	this->m_Triming = data;
}

void CD2D_Font::SetWrapping(DWRITE_WORD_WRAPPING data)
{
	this->Release();
	this->m_Wrapping = data;
}

void CD2D_Font::SetFontWeight(DWRITE_FONT_WEIGHT data)
{
	if (this->m_pTextFormat != NULL)
	{
		this->m_pTextFormat->Release();
		this->m_pTextFormat = NULL;
	}
	this->m_FontWeight = data;
}

void CD2D_Font::SetFontStyle(DWRITE_FONT_STYLE data)
{
	this->Release();
	this->m_FontStyle = data;
}

void CD2D_Font::SetFontStretch(DWRITE_FONT_STRETCH data)
{
	this->Release();
	this->m_FontStretch = data;
}

void CD2D_Font::SetUnderLine(bool data)
{
	this->m_IsUnderLine = data;
}

void CD2D_Font::SetFontSize(float data)
{
	this->Release();
	this->m_FontSize = data;
}

void CD2D_Font::SetFontName(const wstring& name)
{
	this->Release();
	this->m_FontName = name;
}

void CD2D_Font::CreateFont_()
{
	this->Release();

	HRESULT hr = CD2D_Font::m_pDWriteFactory->CreateTextFormat(
		this->m_FontName.c_str(),                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		this->m_FontWeight,
		this->m_FontStyle,
		this->m_FontStretch,
		this->m_FontSize,
		L"en-us",
		&this->m_pTextFormat
	);

	this->m_pTextFormat->SetWordWrapping(this->m_Wrapping);

	if (this->m_Triming != DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_NONE)
	{
		m_pDWriteFactory->CreateEllipsisTrimmingSign(this->m_pTextFormat, &this->m_pTrimeObject);

		DWRITE_TRIMMING trim1;
		trim1.granularity = this->m_Triming;
		trim1.delimiter = 1;
		trim1.delimiterCount = 24;

		hr = this->m_pTextFormat->SetTrimming(&trim1, this->m_pTrimeObject);
	}
	
	this->m_pTextFormat->SetTextAlignment(this->m_Aligment);
	
}

D2D1_SIZE_F CD2D_Font::GetTextSize(const wchar_t* data, float width, float height)
{
	D2D1_SIZE_F sz = { 0 };
	HRESULT hr = S_OK;
	hr = m_pDWriteFactory->CreateTextLayout(data, wcslen(data), *this, width, height, &this->m_pTextLayout);

	if (SUCCEEDED(hr))
	{
		if (this->m_IsUnderLine == true)
		{
			DWRITE_TEXT_RANGE range = { 0 };
			range.length = ::wcslen(data);
			this->m_pTextLayout->SetUnderline(TRUE, range);
		}
		DWRITE_TEXT_METRICS textMetrics;
		hr = this->m_pTextLayout->GetMetrics(&textMetrics);
		sz.width = ceil(textMetrics.widthIncludingTrailingWhitespace);
		sz.height = ceil(textMetrics.height);
	}

	return sz;
}

CD2D_Font::operator IDWriteTextLayout*()
{
	if (this->m_pTextLayout == NULL)
	{
		this->CreateFont_();
	}
	return this->m_pTextLayout;
}

CD2D_Font::operator IDWriteTextFormat*()
{
	if (this->m_pTextFormat == NULL)
	{
		this->CreateFont_();
	}
	return this->m_pTextFormat;
}

void CD2D_Font::Release()
{
	if (this->m_pTextFormat != NULL)
	{
		this->m_pTextFormat->Release();
		this->m_pTextFormat = NULL;
	}
	if (this->m_pTextLayout != NULL)
	{
		this->m_pTextLayout->Release();
		this->m_pTextLayout = NULL;
	}
	if (this->m_pTrimeObject != NULL)
	{
		this->m_pTrimeObject->Release();
		this->m_pTrimeObject = NULL;
	}
}