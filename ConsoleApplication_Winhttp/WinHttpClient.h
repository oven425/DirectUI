#pragma once
#include <memory>
using namespace std;

#include <Windows.h>
#include <atlstr.h>
#include <winhttp.h>
#pragma comment(lib, "WinHTTP.lib")


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
    WinHttpResponse(HINTERNET request)
    {
        hRequest = request;
    }
    //void GetStatusCode()
    //{
    //    //WINHTTP_QUERY_STATUS_CODE
    //    //DWORD dwStatusCode = 0;
    //    DWORD SizeHeaders = 0;
    //    DWORD dwSize = sizeof(DWORD);
    //    auto bResults = WinHttpQueryHeaders(this->hRequest,
    //        WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
    //        NULL,
    //        &m_StatusCode,
    //        &dwSize,
    //        WINHTTP_NO_HEADER_INDEX);
    //    //return dwStatusCode;
    //}
    CString ReadAsString()
    {
        return _T("");
    }
private:
    HINTERNET hRequest = NULL;
};

class WinHttpClient final
{
public:
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
    unique_ptr<WinHttpResponse> Get(const CString& url)
	{
        auto uri = WinHttpUri(url);

        DWORD dwSize = 0;
        DWORD dwDownloaded = 0;
        LPSTR pszOutBuffer;
        BOOL  bResults = FALSE;

        // Use WinHttpOpen to obtain a session handle.
        hSession = WinHttpOpen(L"WinHTTP Example/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS, 0);

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
            auto resp = ::make_unique< WinHttpResponse>(hRequest);
            return resp;
        }
        else
        {
            
        }
        
        //// Keep checking for data until there is nothing left.
        //if (bResults)
        //    do
        //    {
        //        // Check for available data.
        //        dwSize = 0;
        //        if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
        //            printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());

        //        // Allocate space for the buffer.
        //        pszOutBuffer = new char[dwSize + 1];
        //        if (!pszOutBuffer)
        //        {
        //            printf("Out of memory\n");
        //            dwSize = 0;
        //        }
        //        else
        //        {
        //            // Read the Data.
        //            ZeroMemory(pszOutBuffer, dwSize + 1);

        //            if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
        //                dwSize, &dwDownloaded))
        //                printf("Error %u in WinHttpReadData.\n", GetLastError());
        //            else
        //                printf("%s\n", pszOutBuffer);

        //            // Free the memory allocated to the buffer.
        //            delete[] pszOutBuffer;
        //        }

        //    } while (dwSize > 0);


        //    // Report any errors.
        //    if (!bResults)
        //        printf("Error %d has occurred.\n", GetLastError());
	}
private:
    HINTERNET hSession = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
};




