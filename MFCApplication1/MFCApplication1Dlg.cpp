
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

void CMFCApplication1Dlg::DragFiles(const shared_ptr<CControl> sender, const DragFilesArgs& args)
{

}

void CMFCApplication1Dlg::TestUnique(const CTT*  data)
{
	map<const CTT*, int> mm;
	mm[data] = 1;
}
// CMFCApplication1Dlg 訊息處理常式
#include <array>
#include <variant>
using namespace std;
std::weak_ptr<int> gw;
map<int, weak_ptr<int>> mm;

void observe()
{
	shared_ptr<int> pp = ::make_shared<int>(5);
	int pp_use_count = pp.use_count();
	mm[1] = pp;
	pp_use_count = pp.use_count();
	std::cout << "pp use_count == " << pp.use_count() << ": ";
	std::cout << "use_count == " << gw.use_count() << ": ";
	if (auto spt = gw.lock()) { // Has to be copied into a shared_ptr before usage
		std::cout << *spt << "\n";
	}
	else {
		std::cout << "gw is expired\n";
	}
}

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	
	{
		auto sp = std::make_shared<int>(42);
		gw = sp;
		std::weak_ptr<int> gw1 = gw;
		observe();
		if (gw.lock())
		{

		}
	}
	observe();
	auto pp = mm[1];
	auto lll = pp.lock();
	std::variant<int, string, weak_ptr<void>> a,b,c;
	a = 10;
	a = "321";
	a = 1.1111;
	b = "123";
	c = ::make_shared<CCanvas>();
	auto aaaa = std::get<weak_ptr<void>>(c);
	//unique_ptr<CTT> iint = ::make_unique<CTT>();
	//this->TestUnique(&*iint);
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
	shared_ptr<CD2D_SolidColorBrush> br = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red));
	shared_ptr<void> aa = br;
	shared_ptr<CD2D_SolidColorBrush> br1 = static_pointer_cast<CD2D_SolidColorBrush>(aa);

	shared_ptr<float> ff = ::make_shared<float>(5);
	float& ii = *ff;
	ii = 100;
	shared_ptr<void> ff_save = ff;
	*ff = 10;
	if (ff_save == ff)
	{
		::OutputDebugStringA("");
	}

	//CDirectUI_Size sz1(100, 200);
	//CDirectUI_Size sz2 = sz1.SetWidth1(300);
	
	//array< D2D1_GRADIENT_STOP, 2> gradientStops;
	////D2D1_GRADIENT_STOP gradientStops[2];
	//gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
	//gradientStops[0].position = 0.0f;
	//gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1);
	//gradientStops[1].position = 1.0f;

	windows->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red)));
	windows->Name = L"windows";


	//shared_ptr<DirectUI::Control::CButton> button = ::make_shared<DirectUI::Control::CButton>();
	//button->SetContent(L"Test Test Test");
	//button->Name = L"button";
	//button->SetMargin(CDirectUI_Thinkness(10));
	//button->SetHorizontalAlignment(HorizontalAlignments::Right);
	//button->SetVerticalAlignment(VerticalAlignments::Bottom);
	//button->MouseClickHandler = [](auto sender, auto args)
	//{
	//	::OutputDebugStringA("button mouse click\r\n");
	//};
	//button->MouseLeftButtonDownHandler = [](auto sender, auto args)
	//{
	//	::OutputDebugStringA("button left button dwon\r\n");
	//};
	//button->MouseLeftButtonUpHandler = [](auto sender, auto args)
	//{
	//	::OutputDebugStringA("button left button up\r\n");
	//};
	//button->MouseEnterHandler = [](auto sender, auto args)
	//{
	//	::OutputDebugStringA("button mouse enter up\r\n");
	//};
	//button->MouseLeaveHandler = [](auto sender, auto args)
	//{
	//	::OutputDebugStringA("button mouse leave\r\n");
	//};
	//windows->SetChild(button);

	//shared_ptr<CCanvas> canvas = ::make_shared<CCanvas>();
	//canvas->SetBackground(::make_shared< CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue)));
	//shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>(L"sample.jpg");
	////imgsource->Open(L"sample.jpg");
	//shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//image->SetSource(imgsource);
	//image->SetStretch(Stretchs::None);
	////image->SetHieght(100);
	////image->SetHorizontalAlignment(HorizontalAlignments::Right);
	////image->SetVerticalAlignment(VerticalAlignments::Bottom);
	//image->Name = L"image";
	////image->Margin = CDirectUI_Thinkness(10);
	//canvas->AddChild(image);
	//windows->SetChild(canvas);

	//shared_ptr<CBorder> border = ::make_shared<CBorder>();
	//border->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f)));
	//border->Name = L"border";
	////border->SetCornerRadius(CDirectUI_CornerRadius(20));
	//border->SetBorderThickness(CDirectUI_Thinkness(10));
	//border->SetBorderBrush(::make_shared<CD2D_SolidColorBrush>(CDirectUI_Color(255,0,0)));
	//border->SetBorderBrush(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f)));
	////border->SetWidth(200);
	//border->SetHorizontalAlignment(HorizontalAlignments::Center);
	////border->SetVerticalAlignment(VerticalAlignments::Bottom);
	////border->SetMargin(CDirectUI_Thinkness(20));
	////border->SetPadding(CDirectUI_Thinkness(40));
	//shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//imgsource->Open(L"sample.jpg");
	//shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//image->SetSource(imgsource);
	//image->SetStretch(Stretchs::Uniform);
	////image->SetHieght(100);
	////image->SetHorizontalAlignment(HorizontalAlignments::Right);
	////image->SetVerticalAlignment(VerticalAlignments::Bottom);
	//image->Name = L"image";
	////image->Margin = CDirectUI_Thinkness(10);
	//border->SetChild(image);

	//shared_ptr<CTextBlock> textblock = ::make_shared<CTextBlock>();
	//textblock->Name = L"text";
	////textblock->SetHorizontalAlignment(HorizontalAlignments::Center);
	////textblock->SetVerticalAlignment(VerticalAlignments::Center);
	//textblock->SetForeground(::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black)));
	//textblock->SetBackground(::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Purple)));
	//textblock->SetText(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	//border->SetChild(textblock);
	//windows->SetChild(border);


	//shared_ptr<CStackPanel> stackpanel = ::make_shared<CStackPanel>();
	//stackpanel->SetMargin(CDirectUI_Thinkness(10));
	//stackpanel->SetOrientation(Orientations::Horizontal);
	////stackpanel->SetHorizontalAlignment(HorizontalAlignments::Center);
	////stackpanel->SetVerticalAlignment(VerticalAlignments::Bottom);
	//stackpanel->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Purple, 1.0f)));
	//for (int i = 0; i < 3; i++)
	//{
	//	//shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//	//imgsource->Open(L"sample.jpg");
	//	//shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//	//image->SetSource(imgsource);
	//	////image->SetStretch((Stretchs)i);
	//	////image->SetVerticalAlignment((VerticalAlignments)i);
	//	////image->SetVerticalAlignment((VerticalAlignments::Bottom));
	//	////image->SetHieght(150);

	//	////image->SetHorizontalAlignment((HorizontalAlignments)i);
	//	////image->SetWidth(150);
	//	//image->SetStretch(Stretchs::Fill);
	//	//stackpanel->AddChild(image);
	//	shared_ptr<DirectUI::Control::CButton> button = ::make_shared<DirectUI::Control::CButton>();
	//	wchar_t name[265] = { 0 };
	//	::swprintf_s(name, L"button_%d", i);
	//	button->SetContent(name);
	//	stackpanel->AddChild(button);
	//}
	//
	//windows->SetChild(stackpanel);

	//shared_ptr<CUniformGrid> uniformgrid = ::make_shared<CUniformGrid>();
	//uniformgrid->Name = L"uniformgrid";
	//uniformgrid->SetMargin(CDirectUI_Thinkness(10));
	////uniformgrid->SetHorizontalAlignment(HorizontalAlignments::Left);
	////uniformgrid->SetVerticalAlignment(VerticalAlignments::Center);
	////uniformgrid->SetColums(5);
	////uniformgrid->SetRows(5);
	//uniformgrid->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f)));
	//for (int i = 0; i < 4; i++)
	//{
	//	//shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//	//imgsource->Open(L"sample.jpg");
	//	//shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//	//image->SetSource(imgsource);
	//	//image->SetStretch((Stretchs)i);
	//	////image->SetVerticalAlignment((VerticalAlignments)i);
	//	////image->SetVerticalAlignment((VerticalAlignments::Bottom));
	//	////image->SetHieght(100);

	//	////image->SetHorizontalAlignment((HorizontalAlignments)i);
	//	////image->SetWidth(300);
	//	////image->SetStretch(Stretchs::Fill);
	//	//uniformgrid->AddChild(image);

	//	shared_ptr<DirectUI::Control::CButton> button = ::make_shared<DirectUI::Control::CButton>();
	//	wchar_t name[265] = { 0 };
	//	::swprintf_s(name, L"button_%d", i);
	//	button->SetContent(name);
	//	uniformgrid->AddChild(button);

	//	//shared_ptr<DirectUI::Control::CTextBlock> textblock = ::make_shared<DirectUI::Control::CTextBlock>();
	//	//wchar_t name[265] = { 0 };
	//	//::swprintf_s(name, L"textblock_%d", i);
	//	//textblock->Name = name;
	//	//textblock->SetText(name);
	//	//textblock->SetHorizontalAlignment(HorizontalAlignments::Right);
	//	//textblock->SetVerticalAlignment(VerticalAlignments::Top);
	//	//textblock->SetForeground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black, 1.0f)));
	//	//textblock->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f)));
	//	//uniformgrid->AddChild(textblock);

	//}
	//windows->SetChild(uniformgrid);

	//shared_ptr<CGrid> grid = ::make_shared<CGrid>();
	//grid->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f)));
	//vector<shared_ptr<CGridColumnDefinition>> cols;
	//cols.push_back(::make_shared<CGridColumnDefinition>());
	//cols.push_back(::make_shared<CGridColumnDefinition>());
	//vector<shared_ptr<CGridRowDefintion>> rows;
	//rows.push_back(::make_shared<CGridRowDefintion>());
	//rows.push_back(::make_shared<CGridRowDefintion>());
	//grid->SetRowDefinitions(rows);
	//grid->SetColumnDefinitions(cols);
	//for (int i = 0; i < 4; i++)
	//{
	//	shared_ptr<DirectUI::Control::CButton> button = ::make_shared<DirectUI::Control::CButton>();
	//	wchar_t name[265] = { 0 };
	//	::swprintf_s(name, L"button_%d", i);
	//	button->SetContent(name);
	//	button->Name = name;
	//	grid->AddCild(button);
	//	
	//}
	//windows->SetChild(grid);

	//shared_ptr<CBorder> border = ::make_shared<CBorder>();
	//border->SetBorderBrush(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f)));
	//border->SetBorderThickness(10);
	//border->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f)));
	//border->SetMargin(CDirectUI_Thinkness(20));
	////border->SetWidth(300);
	////border->SetHieght(300);
	//border->Name = L"border";
	////border->SetHorizontalAlignment(HorizontalAlignments::Right);
	////border->SetVerticalAlignment(VerticalAlignments::Bottom);
	//windows->SetChild(border);

	//shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//imgsource->Open(L"sample.jpg");
	//shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//image->SetSource(imgsource);
	//image->SetStretch(Stretchs::None);
	////image->SetHieght(100);
	//image->SetHorizontalAlignment(HorizontalAlignments::Right);
	////image->SetVerticalAlignment(VerticalAlignments::Bottom);
	//image->Name = L"image";
	//image->SetMargin(CDirectUI_Thinkness(10,20,40,60));
	//windows->SetChild(image);

	//shared_ptr<DirectUI::Control::CTextBlock> textblock = ::make_shared<DirectUI::Control::CTextBlock>();
 //   textblock->Font = ::make_shared<CD2D_Font>();
	//textblock->Font->SetFontSize(32);
	////textblock->Font->SetFontWeight();
	////textblock->Font->SetFontStyle();
	////textblock->Font->SetUnderLine(true);
	////textblock->Font->SetFontName(CD2D_Font::GetFontNmaes()[0]);
	////textblock->Font->SetTriming(DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER);
	////textblock->Font->SetAligment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_TRAILING);
	//textblock->SetText(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	////textblock->SetText(L"abc defghij klmnopqrstuvWXYZ");
	//textblock->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black, 1.0f)));
	//textblock->SetForeground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::White, 1.0f)));
	//textblock->Name = L"textblock";
	//textblock->SetMargin(CDirectUI_Thinkness(10, 20, 40, 60));
	//textblock->SetWidth(200);
	////textblock->SetHieght(10);

	////textblock->SetHorizontalAlignment(HorizontalAlignments::Right);
	////textblock->SetVerticalAlignment(VerticalAlignments::Bottom);
	//windows->SetChild(textblock);


	//shared_ptr<CThumb> thumb = ::make_shared<CThumb>();
	//thumb->SetBackground(make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f)));
	//thumb->SetWidth(200);
	//thumb->SetHieght(300);
	//thumb->DragStartedHandler = [](auto sender, auto args)
	//{
	//	char msg[256] = { 0 };
	//	::sprintf_s(msg, "Start OffsetX:%f, OffsetY:%d\r\n", args.HorizontalOffset, args.VerticalOffset);
	//	::OutputDebugStringA(msg);
	//};
	//thumb->DragDeltaHandler = [](auto sender, const DragDeltaEventArgs& args)
	//{
	//	char msg[256] = { 0 };
	//	::sprintf_s(msg, "Start ChangeX:%f, ChangeY:%f\r\n", args.HorizontalChange, args.VerticalChange);
	//	::OutputDebugStringA(msg);
	//};
	//thumb->DragCompletedHandler=[](auto sender, auto args)
	//{
	//	char msg[256] = { 0 };
	//	::sprintf_s(msg, "Start ChangeX:%f, ChangeY:%f\r\n", args.HorizontalChange, args.VerticalChange);
	//	::OutputDebugStringA(msg);
	//};
	//windows->SetChild(thumb);


	shared_ptr<CCanvas> canvas = ::make_shared<CCanvas>();
	canvas->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f)));

	shared_ptr<CThumb> thumb = ::make_shared<CThumb>();
	thumb->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f)));
	thumb->SetWidth(100);
	thumb->SetHieght(100);
	canvas->AddChild(thumb);
	thumb->DragStartedHandler = [](auto sender, auto args)
	{
		char msg[256] = { 0 };
		::sprintf_s(msg, "Start OffsetX:%f, OffsetY:%d\r\n", args.HorizontalOffset, args.VerticalOffset);
		//::OutputDebugStringA(msg);
	};
	thumb->DragDeltaHandler = [](auto sender, const DragDeltaEventArgs& args)
	{
		//char msg[256] = { 0 };
		//::sprintf_s(msg, "Start ChangeX:%f, ChangeY:%f\r\n", args.HorizontalChange, args.VerticalChange);
		//::OutputDebugStringA(msg);
		float pos_left = CCanvas::GetLeft(sender) + args.HorizontalChange;
		float pos_top = CCanvas::GetTop(sender) + args.VerticalChange;
		char msg[256] = { 0 };
		::sprintf_s(msg, "pos_left:%f, pos_top:%f\r\n", pos_left, pos_top);
		::OutputDebugStringA(msg);
		CCanvas::SetLeft(sender, pos_left);
		CCanvas::SetTop(sender, pos_top);
	};
	thumb->DragCompletedHandler=[](auto sender, auto args)
	{
		char msg[256] = { 0 };
		::sprintf_s(msg, "Start ChangeX:%f, ChangeY:%f\r\n", args.HorizontalChange, args.VerticalChange);
		//::OutputDebugStringA(msg);
	};
	windows->SetChild(canvas);

	//windows.SetMinWidth(300);
	//windows.SetMaxWidth(500);
	windows->Init(this->m_hWnd);
	//windows->test = std::bind(&CMFCApplication1Dlg::DragFiles, this, std::placeholders::_1, std::placeholders::_2);
	windows->DragHandler = [](const shared_ptr<CControl> sender, const DragFilesArgs& args)
	{
		for (auto oo : args.files)
		{
			::OutputDebugStringW(oo.c_str());
		}

	};
	windows->SetAllowDropFiles(true);

	windows->SetTitle(L"MainWindow");
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

