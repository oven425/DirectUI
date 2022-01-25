
// MFCApplication_DispatchDlg.h: 標頭檔
//

#pragma once
#include "DispatcherTimer.h"
#include "Dispatch.h"
#include "DispatchObject.h"
#include "EventHandler.h"

// CMFCApplicationDispatchDlg 對話方塊
class CMFCApplicationDispatchDlg : public CDialogEx
{
// 建構
public:
	CMFCApplicationDispatchDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DISPATCH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援
	//Dispatch m_Dispatcher;
	//DispatchObject m_object;
// 程式碼實作
private:
	int m_A = 0;
	int m_B = 0;

protected:
	
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
