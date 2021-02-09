
// MFCApplication1Dlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
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


// CMFCApplication1Dlg 對話方塊



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 訊息處理常式
#include <array>
BOOL CMFCApplication1Dlg::OnInitDialog()
{
	//array<int, 4> tt{ 1,2,3,4 };
	//array<int, 4> tt2;
	//tt2 = tt;
	//int ss = tt.size();
	//int tt1[4] = { 0 };
	//auto aa = &(*tt.begin());
	//::memcpy(tt1, aa, ss*sizeof(int));
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
	
	
	array< D2D1_GRADIENT_STOP, 2> gradientStops;
	//D2D1_GRADIENT_STOP gradientStops[2];
	gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1);
	gradientStops[1].position = 1.0f;

	windows.Background = ::make_shared<CD2D_LinearGradientBrush>(&(*gradientStops.begin()), 2);
	windows.Name = L"windows";

	shared_ptr<CBorder> border = ::make_shared<CBorder>();
	//border->Background = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Purple, 1.0f));
	border->SetCornerRadius(CDirectUI_CornerRadius(20, 40, 60, 80));
	border->SetBorderThickness(CDirectUI_Thinkness(20, 40, 60, 80));
	border->BorderBrush = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red, 1.0f));
	windows.m_Child = border;


	//shared_ptr<CStackPanel> stackpanel = ::make_shared<CStackPanel>();
	//stackpanel->Margin = CDirectUI_Thinkness(10);
	//stackpanel->SetOrientation(Orientations::Horizontal);
	////stackpanel->SetHorizontalAlignment(HorizontalAlignments::Center);
	//stackpanel->SetVerticalAlignment(VerticalAlignments::Bottom);
	//stackpanel->Background = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red, 1.0f));
	//for (int i = 0; i < 3; i++)
	//{
	//	shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//	imgsource->Open(L"sample.jpg");
	//	shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//	image->SetSource(imgsource);
	//	//image->SetStretch((Stretchs)i);
	//	//image->SetVerticalAlignment((VerticalAlignments)i);
	//	//image->SetVerticalAlignment((VerticalAlignments::Bottom));
	//	image->SetHieght(150);

	//	//image->SetHorizontalAlignment((HorizontalAlignments)i);
	//	image->SetWidth(150);
	//	image->SetStretch(Stretchs::Fill);
	//	stackpanel->AddChild(image);
	//}
	//
	//windows.m_Child = stackpanel;

	//shared_ptr<CUniformGrid> uniformgrid = ::make_shared<CUniformGrid>();
	//uniformgrid->Name = L"uniformgrid";
	////uniformgrid->Margin = CDirectUI_Thinkness(10);
	////uniformgrid->SetHorizontalAlignment(HorizontalAlignments::Left);
	//uniformgrid->SetVerticalAlignment(VerticalAlignments::Center);
	////uniformgrid->SetColums(5);
	////uniformgrid->SetRows(5);
	//uniformgrid->Background = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red, 1.0f));
	//for (int i = 0; i < 4; i++)
	//{
	//	shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//	imgsource->Open(L"sample.jpg");
	//	shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//	image->SetSource(imgsource);
	//	image->SetStretch((Stretchs)i);
	//	//image->SetVerticalAlignment((VerticalAlignments)i);
	//	//image->SetVerticalAlignment((VerticalAlignments::Bottom));
	//	//image->SetHieght(100);

	//	//image->SetHorizontalAlignment((HorizontalAlignments)i);
	//	//image->SetWidth(300);
	//	//image->SetStretch(Stretchs::Fill);
	//	uniformgrid->AddChild(image);

	//}
	//windows.m_Child = uniformgrid;

	//shared_ptr<CBorder> border = ::make_shared<CBorder>();
	//border->BorderBrush = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red, 1.0f));
	//border->BorderThickness = 2;
	//border->Margin = CDirectUI_Thinkness(5);
	//border->SetWidth(300);
	//border->SetHieght(300);
	//border->Name = L"border";
	//border->SetHorizontalAlignment(HorizontalAlignments::Right);
	//border->SetVerticalAlignment(VerticalAlignments::Bottom);
	//windows.m_Child = border;

	//shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//imgsource->Open(L"sample.jpg");
	//shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//image->SetSource(imgsource);
	//image->SetStretch(Stretchs::Uniform);
	//image->SetHieght(100);
	////image->SetHorizontalAlignment(HorizontalAlignments::Right);
	//image->SetVerticalAlignment(VerticalAlignments::Bottom);
	//image->Name = L"image";
	//image->Margin = CDirectUI_Thinkness(10);
	//windows.m_Child = image;

	//shared_ptr<DirectUI::Control::CTextBlock> textblock = ::make_shared<DirectUI::Control::CTextBlock>();
 //   textblock->Font = ::make_shared<CD2D_Font>();
	//textblock->Font->SetFontSize(32);
	////textblock->Font->SetFontWeight();
	////textblock->Font->SetFontStyle();
	////textblock->Font->SetUnderLine(true);
	//textblock->Font->SetFontName(CD2D_Font::GetFontNmaes()[0]);
	////textblock->Font->SetTriming(DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER);
	////textblock->Font->SetAligment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_TRAILING);
	//textblock->SetText(L"白日依山盡,黃河入海流");
	////textblock->SetText(L"abc defghij klmnopqrstuvWXYZ");
	//textblock->Background = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black, 1.0f));
	//textblock->Foreground = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::White, 1.0f));
	//textblock->Name = L"textblock";
	////textblock->Margin = CDirectUI_Thinkness(10,20,40,60);
	////textblock->SetWidth(200);
	////textblock->SetHieght(10);

	////textblock->SetHorizontalAlignment(HorizontalAlignments::Right);
	////textblock->SetVerticalAlignment(VerticalAlignments::Bottom);
	//windows.m_Child = textblock;



	//windows.SetMinWidth(300);
	//windows.SetMaxWidth(500);
	windows.Init(this->m_hWnd);

	

	windows.SetTitle(L"MainWindow");
	//windows.Background1 = new CD2D_SolidColorBrush();
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

