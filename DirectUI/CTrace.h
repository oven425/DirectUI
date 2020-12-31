#pragma once
#include <memory>
#include <string>
#include <stdexcept>
using namespace std;
namespace DirectUI
{
	class CTrace
	{
	public:
		static void WriteLine(const wchar_t* data);
		static void WriteLine(const wstring& data);
		static void Write(const wchar_t* data);
		static void Write(const wstring& data);

		template<typename ... Args>
		static void Write(const wchar_t* format, Args ... args)
		{
			int size = _snwprintf_s(nullptr, 0, _TRUNCATE, format, args ...) + 1; // Extra space for '\0'
			if (size <= 0) { throw std::runtime_error("Error during formatting."); }
			std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);
			_snwprintf(buf.get(), size, format, args ...);
			::OutputDebugStringW(buf.get());
		}

		template<typename ... Args>
		static void WriteLine(const wchar_t* format, Args ... args)
		{
			int size = swprintf(NULL, 0, format, args ...);
			//int size = _snwprintf_s(nullptr, 0, _TRUNCATE, format, args ...) + 1; // Extra space for '\0'
			if (size <= 0) { throw std::runtime_error("Error during formatting."); }
			std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);
			_snwprintf_s(buf.get(), size, _TRUNCATE, format, args ...);
			::OutputDebugStringW(buf.get());
			::OutputDebugStringW(L"\r\n");
		}


	};
}


