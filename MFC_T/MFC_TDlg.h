﻿
// MFC_TDlg.h: 標頭檔
//

#pragma once
#include "Lazy.h"
#include "Graphic.h"
#include "Window.h"

// CMFCTDlg 對話方塊
class CMFCTDlg : public CDialogEx
{
// 建構
public:
	CMFCTDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_T_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;
	Window* m_App = nullptr;
	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
