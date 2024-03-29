﻿
// MFCApplication_DispatchDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication_Dispatch.h"
#include "MFCApplication_DispatchDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationDispatchDlg 對話方塊



CMFCApplicationDispatchDlg::CMFCApplicationDispatchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DISPATCH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDispatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDispatchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


class Action
{
public:
	Action(std::function<void()> action)
		: m_Action(action)
	{}
	std::function<void()> m_Action;
	void Excute()
	{
		this->m_Action();
	}
};
//mouse event
//HwndSource -InputFilterMessage()-> HwndMouseInputProvider -FilterMessage()->ReportInput()->
//InputProviderSite -ReportInput()-> InputManager -ProcessInput()->ProcessStagingArea()->PreProcessInput()->
//MouseDevice -PreProcessInput()->

// CMFCApplicationDispatchDlg 訊息處理常式
#include <queue>
using namespace std;
DispatcherTimer m_Timer;

#define SOME_MACRO(x) (static_cast<decltype(this)>(x))

BOOL CMFCApplicationDispatchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	shared_ptr<DependencyProperty<int>> pp = ::make_shared< DependencyProperty<int>>();
	shared_ptr<void> vv = pp;

	char str[] = "http://c.biancheng.net";
	char *p1 = reinterpret_cast<char*>(str);
	char ff[100] = { 0 };
	::memcpy(ff, p1, 10);
	std::function<void(decltype(*this))> mm;
	auto iu = static_cast<decltype(this)>(this);
	//auto tt = std::remove_reference<decltype(*this)>::type;
	auto canvas = ::make_shared<Canvas>();
	canvas->name = "canvas";
	for (int i = 0; i < 10; i++)
	{
		auto control = ::make_shared<Control>();
		char name[10] = { 0 };
		::sprintf(name, "control_%d", i);
		control->name = name;
		canvas->AddChild(control);
		//auto l = Canvas::GetLeft(control);
		Canvas::SetLeft(control, i);
		//Canvas::SetTop(control, i + 1);
	}
	this->m_Window1 = make_shared<Window>(this->GetDlgItem(IDC_BUTTON1)->m_hWnd);

	

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplicationDispatchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCApplicationDispatchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCApplicationDispatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

