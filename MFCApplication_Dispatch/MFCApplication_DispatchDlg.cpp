
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


// CMFCApplicationDispatchDlg 訊息處理常式
#include <queue>
using namespace std;
DispatcherTimer m_Timer;
 
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
	Visual vv1;
	vv1.name = "vv1";
	Visual::SetTag(vv1, "123");
	auto tag = Visual::GetTag(vv1);
	vv1.SetValue(&Visual::WidthProperty, 1);
	vv1.SetValue(&Visual::WidthProperty, 2);
	auto width = vv1.GetValue(&Visual::WidthProperty);
	vv1.SetValue(&Visual::ThincknessProperty, ::make_shared<Thinckness>(10));
	vv1.SetValue(&Visual::ThincknessProperty, ::make_shared<Thinckness>(20, 40));
	auto value = vv1.GetValue(&Visual::ThincknessProperty);
	Visual vv2;
	vv2.name = "vv2";
	vv2.SetValue(&Visual::WidthProperty, 10);
	vv2.SetValue(&Visual::WidthProperty, 20);
	m_Timer.m_TimeSpan = chrono::milliseconds(10);
	m_Timer.Tick += ([](auto obj, auto args)
		{
			//obj.Stop();
			SYSTEMTIME time = { 0 };
			::GetLocalTime(&time);
			CString str;
			str.AppendFormat(_T("%02d:%02d:%02d.%03d\r\n"), time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
			::OutputDebugStringW(str);
		});



	//EventHandler<void*, int> kkk;
	//kkk += ([](void*, int)
	//	{
	//		::OutputDebugStringA("");
	//	});
	//kkk += ([](void*, int)
	//	{
	//		::OutputDebugStringA("");
	//	});

	m_Timer.Start();

	//kkk.Fire(this, 10);
	//kkk.m_F = [](void*, int) {

	//};
	
	priority_queue<pair<int, Action*>> pp;
	pp.push({ 5, new Action([&] 
		{
			this->m_A = this->m_A + 1;
		}) });
	pp.push({ 4, new Action([&] {}) });
	pp.push({ 6, new Action([&] {}) });
	pp.push({ 3, new Action([&] {}) });
	pp.push({ 7, new Action([&] {}) });
	while (pp.empty() == false)
	{
		auto now = pp.top();
		now.second->Excute();
		pp.pop();
	}

	vector<std::function<void()>> actions;
	actions.push_back([&]
		{
			this->m_A = this->m_B*this->m_B;
		});
	actions.push_back([&]
		{
			this->m_A = this->m_B+this->m_B;
		});
	this->m_B = 5;
	for (auto oo : actions)
	{
		
		oo();
		auto hr = this->m_A;
	}



	std::function<int(int, int)> func;
	std::function<void()> action;
	int a = 0;
	int b = 0;
	func = [](int a, int b)
	{
		return a + b;
	};
	auto c = func(a, b);
	this->m_B = 10;
	action = [&] {
		this->m_A = this->m_B*this->m_B;
	};
	action();
	this->m_A = 0;



	//action = []
	//{
	//	this->m
	//};

	//std::tuple<int, char> foo(10, 'x');
	//auto bar = std::make_tuple("test", 3.1, 14, 'y');

	//std::get<2>(bar) = 100;                                    // access element

	//int myint; char mychar;

	//std::tie(myint, mychar) = foo;                            // unpack elements
	//std::tie(std::ignore, std::ignore, myint, mychar) = bar;  // unpack (with ignore)

	//mychar = std::get<3>(bar);

	//std::get<0>(foo) = std::get<2>(bar);
	//std::get<1>(foo) = mychar;

	//queue<std::tuple<std::mutex,function<void()>>> qq;
	//qq.push(make_tuple(mutex(), [] {}));

	//auto pop1 = qq.front();

	//mutex myint; function<void()> mychar;
	//std::tie(myint, mychar) = qq.front();
	//auto pop = qq.front();
	//std::cout << "foo contains: ";
	//std::cout << std::get<0>(foo) << ' ';
	//std::cout << std::get<1>(foo) << '\n';


	//this->m_Dispatcher.Invoke([] 
	//	{
	//		::OutputDebugStringA("1\r\n");
	//		::Sleep(3000);
	//		::OutputDebugStringA("1-1\r\n");
	//	});
	//this->m_Dispatcher.Invoke([]
	//	{
	//		::OutputDebugStringA("2\r\n");
	//	});
	//this->m_Dispatcher.Invoke([]
	//	{
	//		::OutputDebugStringA("3\r\n");
	//	});
	//this->m_Dispatcher.Invoke([]
	//	{
	//		::OutputDebugStringA("4\r\n");
	//	});


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

