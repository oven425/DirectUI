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
			unique_ptr<wchar_t[]> name1 = make_unique<wchar_t[]>(length + 1);
			//wchar_t* name = new (std::nothrow) wchar_t[length + 1];
			//if (name == NULL)
			//{
			//	hr = E_OUTOFMEMORY;
			//}

			// Get the family name.
			if (SUCCEEDED(hr))
			{
				hr = pFamilyNames->GetString(index, name1.get(), length + 1);
			}
			m_FontNames.push_back(name1.get());
		}
	}
}


vector<wstring>& CD2D_Font::GetFontNmaes()
{
	return CD2D_Font::m_FontNames;
}