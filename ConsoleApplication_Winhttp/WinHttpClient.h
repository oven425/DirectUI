#pragma once
#include <memory>
#include <vector>
using namespace std;

#include <Windows.h>
#include <atlstr.h>
#include <winhttp.h>
#pragma comment(lib, "WinHTTP.lib")
class WinHttpClient;
#include <iostream>
using namespace std;
class GFG {
private:
    int private_variable;

protected:
    int protected_variable;

public:
    GFG()
    {
        private_variable = 10;
        protected_variable = 99;
    }

    // friend class declaration
    friend class F;
};

// Here, class F is declared as a
// friend inside class GFG. Therefore,
// F is a friend of class GFG. Class F
// can access the private members of
// class GFG.
class F {
public:
    void display(GFG& t)
    {
        cout << "The value of Private Variable = "
            << t.private_variable << endl;
        cout << "The value of Protected Variable = "
            << t.protected_variable;
    }
};


//https://learn.microsoft.com/en-us/windows/win32/winhttp/uniform-resource-locators--urls--in-winhttp
class WinHttpUri final
{
public:
    WinHttpUri(const CString& uri)
    {
        DWORD dwUrlLen = 0;

        // Initialize the URL_COMPONENTS structure.
        ZeroMemory(&m_URL_COMPONENTS, sizeof(m_URL_COMPONENTS));
        m_URL_COMPONENTS.dwStructSize = sizeof(m_URL_COMPONENTS);

        // Set required component lengths to non-zero so that they are cracked.
        m_URL_COMPONENTS.dwSchemeLength = (DWORD)-1;
        m_URL_COMPONENTS.dwHostNameLength = (DWORD)-1;
        m_URL_COMPONENTS.dwUrlPathLength = (DWORD)-1;
        m_URL_COMPONENTS.dwExtraInfoLength = (DWORD)-1;

        // Crack the URL.
        if (!WinHttpCrackUrl(uri, (DWORD)uri.GetLength(), 0, &m_URL_COMPONENTS))
            printf("Error %u in WinHttpCrackUrl.\n", GetLastError());
    }

    CString GetHost()
    {
        return CString(m_URL_COMPONENTS.lpszHostName, m_URL_COMPONENTS.dwHostNameLength);
    }
    int GetPort()
    {
        return this->m_URL_COMPONENTS.nPort;
    }
private:
    URL_COMPONENTS m_URL_COMPONENTS = { 0 };
};


class WinHttpResponse final
{
public:
    //friend int add(WinHttpResponse, WinHttpClient);
    WinHttpResponse(WinHttpClient& dd);
    //WinHttpResponse(HINTERNET request)
    //{
    //    hRequest = request;
    //    DWORD SizeHeaders = 0;
    //    DWORD dwSize = sizeof(DWORD);
    //    auto bResults = WinHttpQueryHeaders(this->hRequest,
    //        WINHTTP_QUERY_RAW_HEADERS_CRLF,
    //        NULL,
    //       NULL,
    //        &dwSize,
    //        WINHTTP_NO_HEADER_INDEX);

    //    const TCHAR* hh = new TCHAR[dwSize + 1];
    //    bResults = WinHttpQueryHeaders(this->hRequest,
    //        WINHTTP_QUERY_RAW_HEADERS_CRLF,
    //        NULL,
    //        &hh,
    //        &dwSize,
    //        WINHTTP_NO_HEADER_INDEX);
    //    
    //}
    ~WinHttpResponse()
    {
        if (hRequest != NULL)
        {
            WinHttpCloseHandle(hRequest);
        }
    }
    int GetStatusCode()
    {
        int dwStatusCode;
        //WINHTTP_QUERY_STATUS_CODE
        //DWORD dwStatusCode = 0;
        DWORD SizeHeaders = 0;
        DWORD dwSize = sizeof(DWORD);
        auto bResults = WinHttpQueryHeaders(this->hRequest,
            WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
            NULL,
            &dwStatusCode,
            &dwSize,
            WINHTTP_NO_HEADER_INDEX);
        return dwStatusCode;
    }

    

    CString ReadAsString()
    {
        auto buf = ReadAsByteArray();
        CString content = _T("");
#if UNICODE
        int aa = 0;
        int convertResult = MultiByteToWideChar(CP_UTF8, 0, (char*)buf.data(), buf.size(), NULL, 0);
#else


#endif
        return content;
    }

    vector<unsigned char> ReadAsByteArray()
    {
        BOOL bResults = TRUE;
        DWORD dwSize = 0;
        DWORD dwDownloaded = 0;
        //unsigned char* pszOutBuffer = nullptr;
        vector<unsigned char> result;
        // Keep checking for data until there is nothing left.
       if (bResults)
           do
           {
               // Check for available data.
               dwSize = 0;
               if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                   printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());

               // Allocate space for the buffer.
               //pszOutBuffer = new unsigned char[dwSize + 1];
               vector<unsigned char> hh(dwSize);
               //if (!pszOutBuffer)
               //{
               //    printf("Out of memory\n");
               //    dwSize = 0;
               //}
               //else
               {
                   // Read the Data.
                   //ZeroMemory(pszOutBuffer, dwSize + 1);

                   if (!WinHttpReadData(hRequest, (LPVOID)hh.data(),
                       dwSize, &dwDownloaded))
                       printf("Error %u in WinHttpReadData.\n", GetLastError());
                   else
                       result.insert(result.end(), hh.begin(), hh.end());
                       //printf("%s\n", pszOutBuffer);

                   // Free the memory allocated to the buffer.
                   //delete[] pszOutBuffer;
               }

           } while (dwSize > 0);


           // Report any errors.
           if (!bResults)
               printf("Error %d has occurred.\n", GetLastError());
        return result;
    }
    
private:
    HINTERNET hRequest = NULL;
};

class WinHttpClient final
{
public:
    WinHttpClient()
        : hSession(NULL)
        , hConnect(NULL)
        , hRequest(NULL)
    {
        // Use WinHttpOpen to obtain a session handle.
        hSession = WinHttpOpen(L"WinHTTP Example/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS, 0);
    }
    ~WinHttpClient()
    {
        if (hSession != NULL)
        {
            WinHttpCloseHandle(hSession);
        }
        if (hConnect != NULL)
        {
            WinHttpCloseHandle(hConnect);
        }
        if (hRequest != NULL)
        {
            WinHttpCloseHandle(hRequest);
        }
    }
    CString GetWinhttpErrorMessage()
    {
        DWORD error = GetLastError();

        if (error)
        {
            LPVOID lpMsgBuf = NULL;
            auto h = ::GetModuleHandle(_T("Winhttp.dll"));
            DWORD bufLen = FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS |
                FORMAT_MESSAGE_FROM_HMODULE,
                h,
                error,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (TCHAR*)&lpMsgBuf,
                0, NULL);
            if (bufLen)
            {
                auto lpMsgStr = (TCHAR*)lpMsgBuf;
                CString result(lpMsgStr, bufLen);
                LocalFree(lpMsgBuf);
                return result;
            }
        }
        return _T("");
    }
    friend class WinHttpResponse;
    unique_ptr<WinHttpResponse> Get(const CString& url)
	{
        auto uri = WinHttpUri(url);

        DWORD dwSize = 0;
        DWORD dwDownloaded = 0;
        LPSTR pszOutBuffer;
        BOOL  bResults = FALSE;

        //// Use WinHttpOpen to obtain a session handle.
        //hSession = WinHttpOpen(L"WinHTTP Example/1.0",
        //    WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        //    WINHTTP_NO_PROXY_NAME,
        //    WINHTTP_NO_PROXY_BYPASS, 0);

        // Specify an HTTP server.
        if (hSession)
            hConnect = WinHttpConnect(hSession, uri.GetHost(), uri.GetPort(), 0);

        // Create an HTTP request handle.
        if (hConnect)
            hRequest = WinHttpOpenRequest(hConnect, _T("GET"), NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

        // Send a request.
        if (hRequest)
            bResults = WinHttpSendRequest(hRequest,
                WINHTTP_NO_ADDITIONAL_HEADERS,
                0, WINHTTP_NO_REQUEST_DATA, 0,
                0, 0);


        // End the request.
        if (bResults)
            bResults = WinHttpReceiveResponse(hRequest, NULL);
        if (bResults)
        {
            auto resp = ::make_unique<WinHttpResponse>(*this);
            hRequest = NULL;
            return resp;
        }
        else
        {
            
        }
	}
private:
    HINTERNET hSession = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
};




