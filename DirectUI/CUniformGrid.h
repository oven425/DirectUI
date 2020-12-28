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
			virtual void OnSize(double width, double height, double dpiscale) override;
			virtual void Measure(double width, double height) override;
			virtual void Arrange(double x, double y, double width, double height) override;
			void SetRows(int data);
			void SetColums(int data);
			int GetRows(int data) { return this->m_Rows; }
			int GetColums(int data) { return this->m_Columns; }
		protected:
			vector <shared_ptr<CControl>> m_Childs;
			int m_Rows = 0;
			int m_Columns = 0;
		};
	}
}

