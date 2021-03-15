#include "pch.h"
#include "CStackPanel.h"
using namespace DirectUI;
using namespace Control;

void CStackPanel::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
	m_Parent.SetValue(data, this->shared_from_this());
}

void CStackPanel::OnSize(float width, float height, float dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
	for (auto oo : this->m_Childs)
	{
		oo->OnSize(width, height, dpiscale);
	}
}

void CStackPanel::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);
	pCompatibleRenderTarget->BeginDraw();

	if (this->m_Background)
	{
		this->m_Background->Refresh(pCompatibleRenderTarget);
		CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
		//CDirectUI_Rect rc(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		pCompatibleRenderTarget->FillRectangle(rc, *this->m_Background);
	}
	for (auto oo : this->m_Childs)
	{
		oo->OnRender(pCompatibleRenderTarget, false);
	}


	pCompatibleRenderTarget->EndDraw();
	ID2D1Bitmap* bmp = NULL;
	pCompatibleRenderTarget->GetBitmap(&bmp);
	CDirectUI_Rect rc_dst = this->m_ActualRect;
	if (calculate_dpi == true)
	{
		rc_dst = this->m_ActualRect / this->m_DpiScale;
	}
	CDirectUI_Rect rc_src(0, 0, this->DesiredSize.width, this->DesiredSize.height);
	//CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	rc_src = this->MappingRenderRect(this->m_ActualRect, this->DesiredSize, this->m_Orientation== Orientations::Vertical, this->m_Orientation == Orientations::Horizontal);

	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);


	bmp->Release();
	pCompatibleRenderTarget->Release();
}

void CStackPanel::Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = this->DesiredSize.height = 0;
	CDirectUI_Size stackpanel_sz = data + this->m_Margin;
	//width = width - this->m_Margin.GetLeft() - this->m_Margin.GetRight();
	//height = height - this->m_Margin.GetTop() - this->m_Margin.GetBottom();
	switch (this->m_Orientation)
	{
	case Orientations::Vertical:
	{
		for (auto oo : this->m_Childs)
		{
			oo->Measure(CDirectUI_Size(stackpanel_sz.GetWidth(), 0), pRT);
			this->DesiredSize.height = this->DesiredSize.height + oo->DesiredSize.height;
		}
		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<CControl> c1, shared_ptr<CControl> c2) {return c1->DesiredSize.width > c2->DesiredSize.width; });
		this->DesiredSize.width = (*aaa)->DesiredSize.width;
	}
	break;
	case Orientations::Horizontal:
	{
		this->DesiredSize.height = stackpanel_sz.GetHeight();
		for (auto oo : this->m_Childs)
		{
			oo->Measure(CDirectUI_Size(0, stackpanel_sz.GetHeight()), pRT);
			this->DesiredSize.width = this->DesiredSize.width + oo->DesiredSize.width;
		}

		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<CControl> c1, shared_ptr<CControl> c2) {return c1->DesiredSize.height > c2->DesiredSize.height; });
		this->DesiredSize.height = (*aaa)->DesiredSize.height;
	}
	break;
	}

	if (this->m_Width > 0 && this->m_Width < this->DesiredSize.width)
	{
		this->DesiredSize.width = this->m_Width;
	}
	else if (this->DesiredSize.width < stackpanel_sz.GetWidth())
	{
		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
		{
			this->DesiredSize.width = stackpanel_sz.GetWidth();
		}
	}
	if (this->m_Height > 0 && this->m_Height < this->DesiredSize.height)
	{
		this->DesiredSize.height = this->m_Height;
	}
	else if (this->DesiredSize.height < stackpanel_sz.GetHeight())
	{
		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
		{
			this->DesiredSize.height = stackpanel_sz.GetHeight();
		}
	}
}

//void CStackPanel::Measure(float width, float height, ID2D1RenderTarget* pRT)
//{
//	this->DesiredSize.width = this->DesiredSize.height = 0;
//	width = width - this->m_Margin.GetLeft() - this->m_Margin.GetRight();
//	height = height - this->m_Margin.GetTop() - this->m_Margin.GetBottom();
//	switch (this->m_Orientation)
//	{
//	case Orientations::Vertical:
//	{
//		for (auto oo : this->m_Childs)
//		{
//			oo->Measure(width, 0, pRT);
//			this->DesiredSize.height = this->DesiredSize.height + oo->DesiredSize.height;
//		}
//		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<CControl> c1, shared_ptr<CControl> c2) {return c1->DesiredSize.width > c2->DesiredSize.width; });
//		this->DesiredSize.width = (*aaa)->DesiredSize.width;
//	}
//	break;
//	case Orientations::Horizontal:
//	{
//		this->DesiredSize.height = height;
//		for (auto oo : this->m_Childs)
//		{
//			oo->Measure(0, height, pRT);
//			this->DesiredSize.width = this->DesiredSize.width + oo->DesiredSize.width;
//		}
//
//		auto aaa = std::max_element(this->m_Childs.begin(), this->m_Childs.end(), [](shared_ptr<CControl> c1, shared_ptr<CControl> c2) {return c1->DesiredSize.height>c2->DesiredSize.height; });
//		this->DesiredSize.height = (*aaa)->DesiredSize.height;
//	}
//	break;
//	}
//
//	if (this->m_Width > 0 && this->m_Width < this->DesiredSize.width)
//	{
//		this->DesiredSize.width = this->m_Width;
//	}
//	else if (this->DesiredSize.width < width)
//	{
//		if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
//		{
//			this->DesiredSize.width = width;
//		}
//	}
//	if (this->m_Height > 0 && this->m_Height < this->DesiredSize.height)
//	{
//		this->DesiredSize.height = this->m_Height;
//	}
//	else if (this->DesiredSize.height < height)
//	{
//		if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
//		{
//			this->DesiredSize.height = height;
//		}
//	}
//}

void CStackPanel::Arrange(float x, float y, float width, float height)
{
	float w = this->DesiredSize.width;
	float h = this->DesiredSize.height;
	if (this->m_HorizontalAlignment == HorizontalAlignments::Stretch)
	{
		if (w > width - this->m_Margin.GetLeft() - this->m_Margin.GetRight())
		{
			w = width - this->m_Margin.GetLeft() - this->m_Margin.GetRight();
		}
	}
	if (this->m_VerticalAlignment == VerticalAlignments::Stretch)
	{
		if (h > height - this->m_Margin.GetTop() - this->m_Margin.GetBottom())
		{
			h = height - this->m_Margin.GetTop() - this->m_Margin.GetBottom();
		}
	}
	switch (this->m_Orientation)
	{
	case Orientations::Vertical:
	{
		float y = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(0, y, w, oo->DesiredSize.height);
			y = y + oo->GetActualRect().GetHeight();
		}
	}
	break;
	case Orientations::Horizontal:
	{
		float x = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(x, 0, oo->DesiredSize.width, h);
			x = x + oo->GetActualRect().GetWidth();
		}
	}
	break;
	}

	CControl::Arrange(x, y, width, height);
}

void CStackPanel::SetOrientation(Orientations data)
{
	this->m_Orientation = data;
}