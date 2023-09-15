// ConsoleApplication_Winhttp.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include "WinHttpClient.h"

std::string ConvertCStringToUTF8(CString strValue)
{
    std::wstring wbuffer;
#ifdef UNICODE
    int aa;
#else
    int aa;

#endif
#ifdef _UNICODE
    wbuffer.assign(strValue.GetString(), strValue.GetLength());
#else
    /*
     * 转换ANSI到UNICODE
     * 获取转换后长度
     */
    int length = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
    wbuffer.resize(length);
    /* 转换 */
    MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif

    /* 获取转换后长度 */
    int length = WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), wbuffer.size(), NULL, 0, NULL, NULL);
    /* 获取转换后内容 */
    std::string buffer;
    buffer.resize(length);

    WideCharToMultiByte(CP_UTF8, 0, strValue, -1, (LPSTR)(buffer.data()), length, NULL, NULL);
    return(buffer);
}

int main()
{
    WinHttpClient httpclient;
    httpclient.Get(_T("https://google.com"));
    //auto resp = httpclient.Get(_T("https://google.com"));
    //auto statuscode = resp->GetStatusCode();
    //auto content_type = resp->GetContentType();
    //auto data1 = resp->ReadAsByteArray();
    //resp = httpclient.Get(_T("https://google.com"));
    //auto data = resp->ReadAsByteArray();

    //auto ddd = ConvertCStringToUTF8(_T("天天開心"));

    //httpclient.UseHttps(false);
    //httpclient.Put("");


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
