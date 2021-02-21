#include "pch.h"
#include "CCanvas.h"
using namespace DirectUI;
using namespace Control;

CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Left;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Right;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Top;
CDependencyObject<shared_ptr<CControl>, float> CCanvas::m_Bottom;

void CCanvas::OnRender(ID2D1RenderTarget* pRT, bool calculate_dpi)
{
	ID2D1BitmapRenderTarget *pCompatibleRenderTarget = NULL;
	HRESULT hr = pRT->CreateCompatibleRenderTarget(this->DesiredSize, &pCompatibleRenderTarget);
	pCompatibleRenderTarget->BeginDraw();
	if (this->m_Background)
	{
		this->m_Background->Refresh(pCompatibleRenderTarget);
		pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0, 0, this->DesiredSize.width, this->DesiredSize.height), *this->m_Background);
	}
	for (auto oo : this->m_Childs)
	{
		oo->OnRender(pCompatibleRenderTarget, calculate_dpi);
	}

	pCompatibleRenderTarget->EndDraw();
	ID2D1Bitmap* bmp = NULL;
	pCompatibleRenderTarget->GetBitmap(&bmp);

	//CDirectUI_Rect rc_dst = this->m_ActualRect / (this->m_DpiScale);
	CDirectUI_Rect rc_dst = this->m_ActualRect;
	if (calculate_dpi == true)
	{
		rc_dst = this->m_ActualRect / this->m_DpiScale;
	}
	//CDirectUI_Rect rc_src(0, 0, this->m_ActualRect.GetWidth(), this->m_ActualRect.GetHeight());
	CDirectUI_Rect rc_src = MappingRenderRect(this->m_ActualRect, this->DesiredSize);
	//rc_src = rc_src / (this->m_DpiScale);
	pRT->DrawBitmap(bmp, rc_dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, rc_src);


	bmp->Release();
	pCompatibleRenderTarget->Release();

}

void CCanvas::Measure(float width, float height, ID2D1RenderTarget* pRT)
{
	this->DesiredSize.width = width;
	this->DesiredSize.height = height;
	for (auto oo : this->m_Childs)
	{
		oo->Measure(0, 0, pRT);
	}
}

void CCanvas::Arrange(float x, float y, float width, float height)
{
	
	for (auto oo : this->m_Childs)
	{
		oo->Arrange(x, y, width, height);
	}
	this->m_ActualRect = CDirectUI_Rect(x, y, x + width, y + height);
}

void CCanvas::SetLeft(shared_ptr<CControl> control, float data)
{
	m_Left.SetValue(control, data);
}

void CCanvas::SetRight(shared_ptr<CControl> control, float data)
{
	m_Right.SetValue(control, data);
}

void CCanvas::SetTop(shared_ptr<CControl> control, float data)
{
	m_Top.SetValue(control, data);
}

void CCanvas::SetBottom(shared_ptr<CControl> control, float data)
{
	m_Bottom.SetValue(control, data);
}

void CCanvas::AddChild(shared_ptr<CControl> data)
{
	this->m_Childs.push_back(data);
	m_Parent.SetValue(data, this->shared_from_this());
}

void CCanvas::RemoveChild(shared_ptr<CControl> data)
{
	for (auto i = this->m_Childs.begin(); i != this->m_Childs.end(); i++)
	{
		if (*i == data)
		{
			this->m_Childs.erase(i);
			break;
		}
	}
	//auto ii = m_Lefts.find(data);
	//if (ii != m_Lefts.end())
	//{
	//	m_Lefts.erase(ii);
	//}
	//ii = m_Rights.find(data);
	//if (ii != m_Rights.end())
	//{
	//	m_Rights.erase(ii);
	//}
	//ii = m_Tops.find(data);
	//if (ii != m_Tops.end())
	//{
	//	m_Tops.erase(ii);
	//}
	//ii = m_Bottoms.find(data);
	//if (ii != m_Bottoms.end())
	//{
	//	m_Bottoms.erase(ii);
	//}
}