
// MFCApplication1Dlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#include"CTT.h"


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

// CMFCApplication1Dlg 訊息處理常式


BOOL CMFCApplication1Dlg::OnInitDialog()
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
	
	//array< D2D1_GRADIENT_STOP, 2> gradientStops;
	////D2D1_GRADIENT_STOP gradientStops[2];
	//gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
	//gradientStops[0].position = 0.0f;
	//gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1);
	//gradientStops[1].position = 1.0f;

	windows->Background = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red));
	windows->Name = L"windows";

	//shared_ptr<Binding<shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>>>> bind = ::make_shared<Data::Binding<shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>>>>();
	//bind->SetSource(CControl::BackgroundPropertyInstance(), windows);
	//windows->SetBinding(CControl::BackgroundPropertyInstance(), bind);

	//shared_ptr<DirectUI::Control::CButton> button = ::make_shared<DirectUI::Control::CButton>();
	//button->SetContent(L"Test Test Test");
	//button->Name = L"button";
	////button->SetMargin(CDirectUI_Thinkness(10));
	////button->SetHorizontalAlignment(HorizontalAlignments::Right);
	////button->SetVerticalAlignment(VerticalAlignments::Bottom);
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
	//border->Background = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f));
	//border->Name = L"border";
	////border->SetCornerRadius(CDirectUI_CornerRadius(20));
	//border->SetBorderThickness(CDirectUI_Thinkness(10));
	//border->BorderBrush = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f));
	//border->SetWidth(400);
	//border->SetHieght(200);
	////border->SetHorizontalAlignment(HorizontalAlignments::Center);
	////border->SetVerticalAlignment(VerticalAlignments::Bottom);
	////border->SetMargin(CDirectUI_Thinkness(20));
	//border->Margin = ::make_shared<CDirectUI_Thinkness>(10);
	//shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//imgsource->Open(L"sample.jpg");
	//shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//image->SetSource(imgsource);
	//image->SetStretch(Stretchs::Uniform);
	////image->SetHieght(100);
	////image->SetHorizontalAlignment(HorizontalAlignments::Right);
	////image->SetVerticalAlignment(VerticalAlignments::Bottom);
	//image->Name = L"image";
	////image->SetMargin = CDirectUI_Thinkness(10);
	////border->SetChild(image);

	//shared_ptr<CTextBlock> textblock = ::make_shared<CTextBlock>();
	//textblock->Name = L"text";
	////textblock->SetHorizontalAlignment(HorizontalAlignments::Center);
	////textblock->SetVerticalAlignment(VerticalAlignments::Center);
	//textblock->SetForeground(::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black)));
	//textblock->SetBackground(::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Purple)));
	//textblock->SetText(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	//textblock->Font->SetFontSize(40);
	////textblock->Margin = ::make_shared<CDirectUI_Thinkness>(10);
	////border->SetChild(textblock);
	//windows->SetChild(border);

	shared_ptr<CStackPanel> stackpanel = ::make_shared<CStackPanel>();
	stackpanel->Name = L"stackpanel";
	stackpanel->Margin = ::make_shared<CDirectUI_Thinkness>(50);
	//stackpanel->VerticalAlignment = VerticalAlignments::Bottom;
	//stackpanel->HorizontalAlignment = HorizontalAlignments::Right;
	stackpanel->Background = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green));
	stackpanel->Orientation = Orientations::Vertical;
	for (int i = 1; i < 5; i++)
	{
		auto ss = L"123456789abcdefghTest_" + std::to_wstring(i+10);
		shared_ptr<CTextBlock> textblock = ::make_shared<CTextBlock>(ss.c_str());
		textblock->Name = L"textblock_" + std::to_wstring(i);
		//textblock->SetHorizontalAlignment(HorizontalAlignments::Left);
		textblock->Font->SetFontSize(20+i*3);
		textblock->Margin = ::make_shared<CDirectUI_Thinkness>(5);
		textblock->Foreground = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black));
		textblock->Background = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Purple));
		stackpanel->AddChild(textblock);
	}

	windows->SetChild(stackpanel);

	//shared_ptr<Shapes::Ellipse> ellipse = ::make_shared<Shapes::Ellipse>();
	////ellipse->SetWidth(100);
	////ellipse->SetHieght(200);
	//ellipse->Stretch = Stretchs::UniformToFill;
	////ellipse->SetHorizontalAlignment(HorizontalAlignments::Right);
	//ellipse->Fill = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue));
	//windows->SetChild(ellipse);

	//shared_ptr<Shapes::Rectangle> rectangle = ::make_shared<Shapes::Rectangle>();
	//rectangle->RadiusX = 50;
	//rectangle->RadiusY = 50;
	//rectangle->SetWidth(200);
	//rectangle->SetHieght(200);
	////rectangle->Stretch = Stretchs::Uniform;
	////rectangle->SetHorizontalAlignment(HorizontalAlignments::Right);
	//rectangle->Fill = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue));
	//windows->SetChild(rectangle);

	//shared_ptr<UniformGrid> uniformgrid = ::make_shared<UniformGrid>();
	//uniformgrid->Background = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green));
	//uniformgrid->Name = L"uniformgrid";
	//uniformgrid->Margin = ::make_shared<CDirectUI_Thinkness>(10);
	//uniformgrid->SetHorizontalAlignment(HorizontalAlignments::Right);
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

	//	//shared_ptr<DirectUI::Control::CButton> button = ::make_shared<DirectUI::Control::CButton>();
	//	//wchar_t name[265] = { 0 };
	//	//::swprintf_s(name, L"button_%d", i);
	//	//button->SetContent(name);
	//	//uniformgrid->AddChild(button);

	//	shared_ptr<DirectUI::Control::CTextBlock> textblock = ::make_shared<DirectUI::Control::CTextBlock>();
	//	wchar_t name[265] = { 0 };
	//	::swprintf_s(name, L"textblock_%d", i);
	//	textblock->Name = name;
	//	textblock->Font->SetFontSize(32);
	//	textblock->SetText(name);
	//	textblock->SetHorizontalAlignment(HorizontalAlignments::Right);
	//	textblock->SetVerticalAlignment(VerticalAlignments::Top);
	//	textblock->SetForeground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black, 1.0f)));
	//	textblock->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f)));
	//	uniformgrid->AddChild(textblock);

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



	//shared_ptr<CD2D_ImageSource> imgsource = ::make_shared<CD2D_ImageSource>();
	//imgsource->Open(L"sample.jpg");
	//shared_ptr<DirectUI::Control::CImage> image = ::make_shared<DirectUI::Control::CImage>();
	//image->SetSource(imgsource);
	//image->SetStretch(Stretchs::None);
	////image->SetHieght(100);
	////image->SetHorizontalAlignment(HorizontalAlignments::Center);
	////image->SetVerticalAlignment(VerticalAlignments::Bottom);
	//image->Name = L"image";
	//image->Margin = ::make_shared<CDirectUI_Thinkness>(30);
	//windows->SetChild(image);

	//shared_ptr<DirectUI::Control::CTextBlock> textblock = ::make_shared<DirectUI::Control::CTextBlock>();
 //   textblock->Font = ::make_shared<CD2D_Font>();
	//textblock->Font->SetFontSize(20);
	////textblock->Font->SetFontWeight();
	////textblock->Font->SetFontStyle();
	////textblock->Font->SetUnderLine(true);
	////textblock->Font->SetFontName(CD2D_Font::GetFontNmaes()[0]);
	////textblock->Font->SetTriming(DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER);
	////textblock->Font->SetAligment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_TRAILING);
	//textblock->SetText(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n1234567890");
	////textblock->SetText(L"abc defghij klmnopqrstuvWXYZ");
	//textblock->Background =::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black, 1.0f));
	//textblock->SetForeground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::White, 1.0f)));
	//textblock->Name = L"textblock";
	//textblock->Margin = make_shared<CDirectUI_Thinkness>(20);
	//textblock->SetWidth(200);
	////textblock->SetHieght(10);

	//textblock->SetHorizontalAlignment(HorizontalAlignments::Left);
	//textblock->SetVerticalAlignment(VerticalAlignments::Bottom);
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


	//shared_ptr<CCanvas> canvas = ::make_shared<CCanvas>();
	//canvas->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f)));

	//shared_ptr<CThumb> thumb = ::make_shared<CThumb>();
	//thumb->SetBackground(::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f)));
	//thumb->SetWidth(100);
	//thumb->SetHieght(100);
	//canvas->AddChild(thumb);
	//thumb->DragStartedHandler = [](auto sender, auto args)
	//{
	//	char msg[256] = { 0 };
	//	::sprintf_s(msg, "Start OffsetX:%f, OffsetY:%f\r\n", args.HorizontalOffset, args.VerticalOffset);
	//	::OutputDebugStringA(msg);
	//};
	//thumb->DragDeltaHandler = [](auto sender, const DragDeltaEventArgs& args)
	//{
	//	//char msg[256] = { 0 };
	//	//::sprintf_s(msg, "Start ChangeX:%f, ChangeY:%f\r\n", args.HorizontalChange, args.VerticalChange);
	//	//::OutputDebugStringA(msg);
	//	float pos_left = CCanvas::GetLeft(sender) + args.HorizontalChange;
	//	float top = CCanvas::GetTop(sender);
	//	float pos_top = top + args.VerticalChange;
	//	char msg[256] = { 0 };
	//	::sprintf_s(msg, "pos_left:%f, top:%f,  ver:%f\r\n", pos_left, top, args.VerticalChange);
	//	::OutputDebugStringA(msg);
	//	CCanvas::SetLeft(sender, pos_left);
	//	CCanvas::SetTop(sender, pos_top);
	//};
	//thumb->DragCompletedHandler=[](auto sender, auto args)
	//{
	//	char msg[256] = { 0 };
	//	::sprintf_s(msg, "Stop ChangeX:%f, ChangeY:%f\r\n", args.HorizontalChange, args.VerticalChange);
	//	::OutputDebugStringA(msg);
	//};
	//windows->SetChild(canvas);


	//shared_ptr<Shapes::Ellipse> ellipse = make_shared<Shapes::Ellipse>();
	//ellipse->Background = make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green, 1.0f));
	//ellipse->Stroke = make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f));
	//ellipse->StrokeThickness = 20;
	//windows->SetChild(ellipse);

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

