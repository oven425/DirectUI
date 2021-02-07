#include "pch.h"
#include "CStackPanel.h"
using namespace DirectUI;
using namespace Control;

void CStackPanel::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
}

void CStackPanel::OnSize(float width, float height, float dpiscale)
{
	::CControl::OnSize(width, height, dpiscale);
	for (auto oo : this->m_Childs)
	{
		oo->OnSize(width, height, dpiscale);
	}
}

void CStackPanel::OnRender(ID2D1RenderTarget* pRT)
{
	//CControl::OnRender(pRT);
	//for(auto oo : this->m_Childs)
	//{
	//	oo->OnRender(pRT);
	//}
	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);
	pCompatibleRenderTarget->BeginDraw();

	if (this->Background)
	{
		this->Background->Refresh(pCompatibleRenderTarget);
		CDirectUI_Rect rc(0, 0, this->DesiredSize.width, this->DesiredSize.height);
		//CDirectUI_Rect rc(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
		pCompatibleRenderTarget->FillRectangle(rc, *this->Background);
	}
	for (auto oo : this->m_Childs)
	{
		oo->OnRender(pCompatibleRenderTarget);
	}


	pCompatibleRenderTarget->EndDraw();
	ID2D1Bitmap* bmp = NULL;
	pCompatibleRenderTarget->GetBitmap(&bmp);
	CDirectUI_Rect rc_dst = this->m_ActualRect / this->m_DpiScale;
	CDirectUI_Rect rc_src(0, 0, this->DesiredSize.width, this->DesiredSize.height);
	//CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	rc_src = this->MappingRenderRect(this->m_ActualRect, this->DesiredSize);
	//if (this->m_ActualRect.GetWidth() < this->DesiredSize.width)
	//{
	//	rc_src.SetX(this->DesiredSize.width - this->m_ActualRect.GetWidth());
	//}
	//CTrace::WriteLine(L"%s render: %s  Desire w:%f h:%f", this->Name.c_str(), rc_src.ToString().c_str(), rc_src.GetWidth(), rc_src.GetHeight());
	//float w1 = rc_dst.GetWidth();
	//float w2 = rc_src.GetWidth();
	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rc_src);


	bmp->Release();
	pCompatibleRenderTarget->Release();
}

void CStackPanel::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	//::CControl::Measure(width, height, pRT);
	this->DesiredSize.width = this->DesiredSize.height = 0;
	switch (this->m_Orientation)
	{
	case Orientations::Vertical:
	{
		for (auto oo : this->m_Childs)
		{
			oo->Measure(width, 0, pRT);
		}
	}
	break;
	case Orientations::Horizontal:
	{
		this->DesiredSize.height = height;
		for (auto oo : this->m_Childs)
		{
			oo->Measure(0, height, pRT);
			this->DesiredSize.width = this->DesiredSize.width + oo->DesiredSize.width;
		}
	}
	break;
	}
}

void CStackPanel::Arrange(float x, float y, float width, float height)
{
	float w = 0;
	switch (this->m_Orientation)
	{
	case Orientations::Vertical:
	{
		double y = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(0, y, width, oo->DesiredSize.height);
			y = y + oo->GetActualRect().GetHeight();
		}
	}
	break;
	case Orientations::Horizontal:
	{
		double x = 0;
		for (auto oo : this->m_Childs)
		{
			oo->Arrange(x, 0, oo->DesiredSize.width, height);
			x = x + oo->GetActualRect().GetWidth();
			w = w + oo->GetActualRect().GetWidth();
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