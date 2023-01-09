
// MFCApplication1Dlg.h: 標頭檔
//

#pragma once
//#include "../DirectUI/CD2D_Font.h"
//using namespace DirectUI;
//using namespace Direct2D;

#include "../DirectUI/CWindow.h"
#include "../DirectUI/CD2D_SolidColorBrush.h"
#include "../DirectUI/CD2D_LinearGradientBrush.h"
#include "../DirectUI/CBorder.h"
#include "../DirectUI/CStackPanel.h"
#include "../DirectUI/UniformGrid.h"
#include "../DirectUI/CImage.h"
#include "../DirectUI/CTextBlock.h"
#include "../DirectUI/CButton.h"
#include "../DirectUI/CThumb.h"
#include "../DirectUI/CCanvas.h"
#include "../DirectUI/CGrid.h"
#include "../DirectUI/Ellipse.h"
#include "../DirectUI/Rectangle.h"
#include "../DirectUI/Dispatcher.h"
#include "../DirectUI/Binding.h"
#include "../DirectUI/CControl.h"
using namespace DirectUI;
using namespace Threading;
using namespace Data;
using namespace Direct2D;
using namespace Control;
using namespace Shapes;


#include <d2d1_1helper.h>
#include "HotKey.h"

// CMFCApplication1Dlg 對話方塊
class CMFCApplication1Dlg : public CDialogEx
{
// 建構
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援
	shared_ptr<CWindow> windows = ::make_shared<CWindow>();

// 程式碼實作
protected:
	void HotyEvent(int scancode);
	HICON m_hIcon;
	HotKey m_HotKey;
	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void DragFiles(const shared_ptr<CControl> sender, const DragFilesArgs& args);
};
