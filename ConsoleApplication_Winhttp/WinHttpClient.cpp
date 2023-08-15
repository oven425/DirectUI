#include "WinHttpClient.h"
WinHttpResponse::WinHttpResponse(WinHttpClient& dd)
{
	this->hRequest = dd.hRequest;
}