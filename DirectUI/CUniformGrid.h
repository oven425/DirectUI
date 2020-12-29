#pragma once
#include <vector>
using namespace std;

#include "CControl.h"

namespace DirectUI
{
	namespace Control
	{
		class __declspec(dllexport) CUniformGrid : public CControl
		{
		public:
			void AddChild(shared_ptr<CControl> data);
			virtual void OnRender(ID2D1HwndRenderTarget* pRT) override;
			virtual void OnSize(float width, float height, float dpiscale) override;
			virtual void Measure(float width, float height) override;
			virtual void Arrange(float x, float y, float width, float height) override;
			void SetRows(int data);
			void SetColums(int data);
			int GetRows(int data) { return this->m_Rows; }
			int GetColums(int data) { return this->m_Columns; }
		protected:
			void CheckRowCol(double width, double height);
			double m_CellWidth = 0;
			double m_CellHeight = 0;
			int m_CellCount = 0;
			int m_CellRows = 0;
			int m_CellColums = 0;
			vector <shared_ptr<CControl>> m_Childs;
			int m_Rows = 0;
			int m_Columns = 0;
		};
	}
}

