
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
#include <array>
#include <variant>
using namespace std;

shared_ptr<CD2D_Brush> s1;
shared_ptr<CD2D_Brush> s2;

//template<typename T>
//typename std::enable_if<std::is_integral<T>::value|| std::is_floating_point<T>::value, void>::type
//SetValue(T data)
//{
//	//T aa = std::get<T>(test);
//	//if (aa != data)
//	//{
//
//	//}
//}

CTT_Object test;
void PropertyChange(const CTT_Object& sender, const CTTChangeArgs<int>& args)
{

}

void Property1Change(const CTT_Object& sender, const CTTChangeArgs<CD2D_Brush>& args)
{

}

template<class _Ty1, class _Ty2>
	_NODISCARD shared_ptr<_Ty1> static_pointer_cast11(const shared_ptr<_Ty2>& _Other) noexcept
{	// static_cast for shared_ptr that properly respects the reference count control block
	const auto _Ptr = static_cast<typename shared_ptr<_Ty1>::element_type *>(_Other.get());
	return (shared_ptr<_Ty1>(_Other, _Ptr));
}

template<typename T>
shared_ptr<T> Trans(shared_ptr<void> src)
{
	const auto _Ptr = static_cast<typename shared_ptr<T>::element_type *>(src.get());
	return shared_ptr<T>(src, _Ptr);
}

template<typename T, typename = typename enable_if<is_integral<T>::value, void>::type>
void Test(T x)
{
	//return T;
}

template<class T>
struct is_shared_ptr : std::false_type {};

template<class T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

std::variant<int, float, shared_ptr<void>> var;
template<typename T>
void SetValue(T data)
{
	bool bb = is_shared_ptr<T>::value;
	if (bb == true)
	{
		
		//var = static_pointer_cast<void>(data);
	}
	else
	{
		var = data;
	}
}

template<typename T>
void SetValue(shared_ptr<T> data)
{
	var = data;
}

template <class T>
struct getValue {
	getValue() {
		printf("not shared!\n");
	}
};

template <class T>
struct getValue<std::shared_ptr<T> > {
	getValue() {
		printf("shared!\n");
	}
};

template<typename T>
T GetValue()
{
	bool bb = is_shared_ptr<T>::value;
	if (bb == true)
	{
		return T{};
	}
	else
	{
		return std::get<T>(var);
	}
	return T{};
}

shared_ptr<CTT_Propoerty<int>> TestProperty = ::make_shared<CTT_Propoerty<int>>();
shared_ptr<CTT_Propoerty<CD2D_Brush>> Test1Property = ::make_shared<CTT_Propoerty<CD2D_Brush>>();
BOOL CMFCApplication1Dlg::OnInitDialog()
{
	SetValue(make_shared<int>(10));
	getValue<int>();
	getValue<shared_ptr<int>>();
	SetValue(1);
	int temp = GetValue<int>();
	bool bb = is_shared_ptr<int>::value;

	shared_ptr<int> ss;
	bb = is_shared_ptr<shared_ptr<int>>::value;
	//auto l = [](int x) -> int {
	//	return x % 7;
	//};
	//fun(l);
	//Test(1);
	//Test(1.0);
	Event <std::function<void(int a)>> evt;
	evt += [](int a)
	{

	};
	evt += [](int a)
	{

	};
	evt.Fire(10);

	TestProperty->Handler = std::bind(PropertyChange, std::placeholders::_1, std::placeholders::_2);
	Test1Property->Handler = std::bind(Property1Change, std::placeholders::_1, std::placeholders::_2);
	s1 = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red));
	s2 = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green));

	int usecount = s1.use_count();
	weak_ptr<void> vv = s1;
	usecount = s1.use_count();
	usecount = vv.use_count();
	//s1.reset();
	auto vb = vv.lock();
	usecount = vv.use_count();
	//std::shared_ptr<void> pointer = s1;
	//auto ptr = std::make_shared<std::remove_reference<decltype(*s1)>::type>();

	auto hh1 = dynamic_pointer_cast<shared_ptr<CD2D_Brush>>(s1);
	//auto hhr = Trans<CD2D_Brush>(vv);
	//auto tt1 = static_pointer_cast11<CD2D_Brush>(vv);
	//const auto _Ptr = static_cast<typename shared_ptr<CD2D_Brush>::element_type *>(vv.get());
	//auto tt2 = shared_ptr<CD2D_Brush>(vv, _Ptr);
	//test.SetValue(Test1Property, 1);
	//test.SetValue(TestProperty, 2);
	test.SetValue(Test1Property, s1);
	test.SetValue(Test1Property, s2);
	//s2.reset();
	auto getbr = test.GetValue<weak_ptr<void>>(Test1Property);
	//float f = 1.1;
	//int use_count = s1.use_count();
	//test.SetValue(TestProperty, s1);
	//use_count = s1.use_count();
	//test.GetValue<shared_ptr<void>>();
	//test.SetValue(TestProperty, s2);
	//use_count = s1.use_count();
	//dynamic_pointer_cast<shared_ptr<CD2D_SolidColorBrush>>(s1);
	

	//auto weak = std::get<weak_ptr<CD2D_Brush>>(test);
	//auto ss = *weak.lock();
	//test = 1;

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

	windows->Background = ::make_shared<CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Red));
	windows->Name = L"windows";

	shared_ptr<Binding<shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>>>> bind = ::make_shared<Data::Binding<shared_ptr<DependencyProperty<Direct2D::CD2D_Brush>>>>();
	bind->SetSource(CControl::BackgroundPropertyInstance(), windows);
	windows->SetBinding(CControl::BackgroundPropertyInstance(), bind);

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
	//stackpanel->Background = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Green));
	//stackpanel->SetOrientation(Orientations::Horizontal);
	//shared_ptr<Shapes::Ellipse> ellipse = ::make_shared<Shapes::Ellipse>();
	//ellipse->SetWidth(12);
	//ellipse->SetHieght(12);
	//ellipse->Fill = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue));
	//stackpanel->AddChild(ellipse);

	//shared_ptr<CTextBlock> textblock = ::make_shared<CTextBlock>(L"test");
	//textblock->SetForeground(::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Black)));
	//stackpanel->AddChild(textblock);
	//windows->SetChild(stackpanel);

	//shared_ptr<Shapes::Ellipse> ellipse = ::make_shared<Shapes::Ellipse>();
	//ellipse->SetWidth(100);
	//ellipse->SetHieght(200);
	//ellipse->Stretch = Stretchs::Uniform;
	//ellipse->SetHorizontalAlignment(HorizontalAlignments::Right);
	//ellipse->Fill = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue));
	//windows->SetChild(ellipse);

	shared_ptr<Shapes::Rectangle> rectangle = ::make_shared<Shapes::Rectangle>();
	rectangle->RadiusX = 50;
	rectangle->RadiusY = 50;
	rectangle->SetWidth(200);
	rectangle->SetHieght(200);
	//rectangle->Stretch = Stretchs::Uniform;
	rectangle->SetHorizontalAlignment(HorizontalAlignments::Right);
	rectangle->Fill = ::make_shared <CD2D_SolidColorBrush>(D2D1::ColorF(D2D1::ColorF::Blue));
	windows->SetChild(rectangle);

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

