#include "pch.h"
#include "CTextBlock.h"
using namespace DirectUI;
using namespace Control;
#define Test

void CTextBlock::OnRender(ID2D1RenderTarget* pRT)
{
	if (this->m_ActualRect.GetWidth() <= 0 || this->m_ActualRect.GetHeight() <= 0 || this->m_Visibility != Visibilitys::Visible)
	{
		return;
	}
#ifdef Test
	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	HRESULT hr = pRT->CreateCompatibleRenderTarget(this->m_ActualRect, &pCompatibleRenderTarget);
	pCompatibleRenderTarget->BeginDraw();

	if (this->Background)
	{
		this->Background->Refresh(pCompatibleRenderTarget);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
		CDirectUI_Rect rc(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		pCompatibleRenderTarget->FillRectangle(rc, m_pBlackBrush);
	}
	if (this->Foreground)
	{
		this->Foreground->Refresh(pCompatibleRenderTarget);
		CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
		pCompatibleRenderTarget->DrawTextLayout(rc, *this->Font, *this->Foreground);
		//rc = CDirectUI_Rect(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		//pCompatibleRenderTarget->DrawTextW(this->m_Text.c_str(), this->m_Text.length(), *this->Font, rc / this->m_DpiScale, *this->Foreground);
	}


	pCompatibleRenderTarget->EndDraw();
	ID2D1Bitmap* bmp = NULL;
	pCompatibleRenderTarget->GetBitmap(&bmp);
	CDirectUI_Rect rc_dst = this->m_ActualRect / this->m_DpiScale;
	CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	rc_src = this->MappingRenderRect(this->m_ActualRect, this->DesiredSize);
	CTrace::WriteLine(L"%s render: %s  Desire w:%f h:%f", this->Name.c_str(), rc_src.ToString().c_str(), rc_src.GetWidth(), rc_src.GetHeight());

	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);


	bmp->Release();
	pCompatibleRenderTarget->Release();
#else
	if (this->Background)
	{
		this->Background->Refresh(pRT);
		ID2D1Brush* m_pBlackBrush = this->Background->operator ID2D1Brush*();
		CDirectUI_Rect rc(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		pRT->FillRectangle(this->m_ActualRect / this->m_DpiScale, m_pBlackBrush);
	}
	if (this->Foreground)
	{
		this->Foreground->Refresh(pRT);
		CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
		pRT->DrawTextW(this->m_Text.c_str(), this->m_Text.length(), *this->Font, this->m_ActualRect / this->m_DpiScale, *this->Foreground);
	}
#endif

}

void CTextBlock::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	D2D1_SIZE_F sz = this->Font->GetTextSize(this->m_Text.c_str(), width, height);
	this->DesiredSize.width = sz.width;
	this->DesiredSize.height = sz.height;
}

void CTextBlock::Arrange(float x, float y, float width, float height)
{
	::CControl::Arrange(x, y, width, height);
	//D2D1_SIZE_F sz = this->GetSize(width, height);
	//float left = x;
	//float top = y;
	//float right = left + sz.width;
	//float bottom = top + sz.height;
	//float w = right - left;
	//if (this->m_HorizontalAlignment!= HorizontalAlignments::Stretch)
	//{
	//	if (w > this->DesiredSize.width)
	//	{
	//		w = this->DesiredSize.width;
	//	}
	//}
	//float h = bottom - top;
	//if (this->m_VerticalAlignment != VerticalAlignments::Stretch)
	//{
	//	if (h > this->DesiredSize.height)
	//	{
	//		h = this->DesiredSize.height;
	//	}
	//}
	//switch (this->m_HorizontalAlignment)
	//{
	//case HorizontalAlignments::Stretch:
	//{
	//	left = left + (width - w) / 2;
	//	
	//}
	//break;
	//case HorizontalAlignments::Center:
	//{
	//	//w = this->DesiredSize.width;
	//	left = left+(width - w) / 2;
	//}
	//break;
	//case HorizontalAlignments::Left:
	//{
	//	//w = this->DesiredSize.width;
	//}
	//break;
	//case HorizontalAlignments::Right:
	//{
	//	//w = this->DesiredSize.width;
	//	left = left+(width - w);
	//}
	//break;
	//}
	//switch (this->m_VerticalAlignment)
	//{
	//case VerticalAlignments::Stretch:
	//case VerticalAlignments::Center:
	//{

	//	top = top + (height - h)/2;
	//}
	//break;
	//case VerticalAlignments::Top:
	//{
	//	//h = this->DesiredSize.height;
	//}
	//break;
	//case VerticalAlignments::Bottom:
	//{
	//	//h = this->DesiredSize.height;
	//	top = top + (height - h);
	//}
	//break;
	//}

	//this->m_ActualRect.SetLeft(left);
	//this->m_ActualRect.SetTop(top);
	//this->m_ActualRect.SetWidth(w);
	//this->m_ActualRect.SetHeight(h);
}

void CTextBlock::SetText(const wchar_t* data)
{
	this->m_Text = data;
}