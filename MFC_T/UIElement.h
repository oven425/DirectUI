#pragma once
#include <vector>
using namespace std;
#include "Brush.h"
#include "Lazy.h"

#pragma comment(lib, "Dwrite.lib")
class Control
{
public:
	Brush* m_pBackground;
	unsigned int m_Width;
	unsigned int m_Height;
	virtual void Render(ID2D1RenderTarget* target)
	{

	}

	virtual void Measure(int width, int height)
	{
		this->m_Width = width;
		this->m_Height = height;
	}

	virtual void Arrange()
	{

	}
	static Lazy<CComPtr<ID2D1Factory>> m_D2DFactory;
	static Lazy<CComPtr<IDWriteFactory>> m_DWriteFactory;
};

class ContentControl :public Control
{
public:
	Control* m_pControl = nullptr;
	void Render(ID2D1RenderTarget* target) override
	{
		Control::Render(target);
		if (m_pControl != nullptr)
		{
			m_pControl->Render(target);
		}
	}
};

//https://learn.microsoft.com/en-us/windows/win32/directwrite/font-enumeration
class TextBlock :public Control
{
public:
	Brush* m_pForeground;
	CString m_Text;
	void Render(ID2D1RenderTarget* target) override
	{
		ID2D1SolidColorBrush* pBlackBrush_;
		IDWriteTextFormat* pTextFormat_;
		auto hr = target->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&pBlackBrush_
		);
		hr = Control::m_DWriteFactory.Value()->CreateTextFormat(
			L"Arial",                // Font family name.
			NULL,                       // Font collection (NULL sets it to use the system font collection).
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,
			L"en-us",
			&pTextFormat_
		);


		D2D1_RECT_F layoutRect = D2D1::RectF(0,0,this->m_Width, this->m_Height
		);

		target->DrawText(
			this->m_Text,        // The string to render.
			this->m_Text.GetLength(),    // The string's length.
			pTextFormat_,    // The text format.
			layoutRect,       // The region of the window where the text will be rendered.
			pBlackBrush_     // The brush used to draw the text.
		);

		pBlackBrush_->Release();
		pTextFormat_->Release();
	}
};

