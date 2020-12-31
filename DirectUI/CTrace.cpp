#include "pch.h"
#include "CTrace.h"
using namespace DirectUI;

void CTrace::WriteLine(const wchar_t* data)
{
	::OutputDebugStringW(data);
	::OutputDebugStringW(L"\r\n");
}

void CTrace::WriteLine(const wstring& data)
{
	::OutputDebugStringW(data.c_str());
	::OutputDebugStringW(L"\r\n");
}

void CTrace::Write(const wchar_t* data)
{
	::OutputDebugStringW(data);
}

void CTrace::Write(const wstring& data)
{
	::OutputDebugStringW(data.c_str());
}