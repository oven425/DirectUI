#pragma once
#include "CPanel.h"
namespace DirectUI
{
	namespace Control
	{
		enum class GridUnitTypes
		{
			Auto,
			Pixel,
			Start
		};

		class __declspec(dllexport) CGridRowDefintion
		{
		public:
			CGridRowDefintion() {}
			CGridRowDefintion(GridUnitTypes type, float data)
			{
				this->m_Type = type;
				this->m_Height = data;
			}
		private:
			GridUnitTypes m_Type = GridUnitTypes::Start;
			float m_Height = 1;
		};

		class __declspec(dllexport) CGridColumnDefinition
		{
		public:
			CGridColumnDefinition() {}
			CGridColumnDefinition(GridUnitTypes type, float data)
			{
				this->m_Type = type;
				this->m_Width = data;
			}
		private:
			GridUnitTypes m_Type = GridUnitTypes::Start;
			float m_Width = 1;
		};

		class __declspec(dllexport) CGrid : public CPanel
		{
		public:
			CGrid();
			void OnRender(ID2D1RenderTarget* pRT) override;
			void Measure(const CDirectUI_Size& data, ID2D1RenderTarget* pRT) override;
			void Arrange(const CDirectUI_Rect& data) override;
			void SetRowDefinitions(vector<shared_ptr<CGridRowDefintion>> datas);
			void SetColumnDefinitions(vector<shared_ptr<CGridColumnDefinition>> datas);
			static shared_ptr<DependencyProperty> RowProperty;
			static shared_ptr<DependencyProperty> RowSpanProperty;
			static shared_ptr<DependencyProperty> ColumnProperty;
			static shared_ptr<DependencyProperty> ColumnSpanProperty;
			static void PropertyChange(const DependencyObject& sender);
			static void SetRow(shared_ptr<CControl> element, int data);
			static void SetRowSpan(shared_ptr<CControl> element, int data);
			static void SetColumn(shared_ptr<CControl> element, int data);
			static void SetColumnSpan(shared_ptr<CControl> element, int data);
			static int GetRow(shared_ptr<CControl> element);
			static int GetRowSpan(shared_ptr<CControl> element);
			static int GetColumn(shared_ptr<CControl> element);
			static int GetColumnSpan(shared_ptr<CControl> element);
		protected:
			vector<shared_ptr<CGridColumnDefinition>> m_ColumnDefinitions;
			vector<shared_ptr<CGridRowDefintion>> m_RowDefinitions;

		};
	}
}


