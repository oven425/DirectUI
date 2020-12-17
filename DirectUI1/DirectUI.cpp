// DirectUI.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
using namespace std;

#include <functional>
class EventHandler
{
public:
	void addHandler(std::function<void(int)> callback)
	{
		cout << "Handler added..." << endl;
		// Let's pretend an event just occured
		callback(1);
	}
};

class CEventHandler
{
public:
	void operator+=(function<void(int)> callback) { this->m_Callback = callback; }
	void RaiseEvent(int data) { this->m_Callback(data); }
protected:
	function<void(int)> m_Callback;
};

class MyClass
{
public:
	MyClass();

	// Note: No longer marked `static`, and only takes the actual argument
	void Callback(int x);
	EventHandler handler;
private:
	int private_x;
};

MyClass::MyClass()
{
	using namespace std::placeholders; // for `_1`

	private_x = 5;
	handler.addHandler(std::bind(&MyClass::Callback, this, _1));
}

void MyClass::Callback(int x)
{
	// No longer needs an explicit `instance` argument,
	// as `this` is set up properly
	cout << x + private_x << endl;
}
void freeStandingCallback(int x)
{
	// ...
}

int main()
{
	CEventHandler eee;
	eee += freeStandingCallback;
	eee.RaiseEvent(5);
	//MyClass mm;
	//mm.handler.addHandler(freeStandingCallback);
    std::cout << "Hello World!\n";
}


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
