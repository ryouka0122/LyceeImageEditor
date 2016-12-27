#include "Functions.h"



void lycee::Log::debug(std::string fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int len = _vscprintf(fmt.c_str(), args) + 1;
	if (len == 1) return;
	
	char *buffer = (char*)malloc(len * sizeof(char));
	memset(buffer, len * sizeof(char), 0);
	
	vsprintf_s(buffer, len, fmt.c_str(), args);
	OutputDebugStringA(buffer);

	free(buffer);
}

void lycee::Log::debug(std::wstring fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int len = _vscwprintf(fmt.c_str(), args) + 1;
	if (len == 1) return;
	
	wchar_t *buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
	memset(buffer, len * sizeof(char), 0);

	vswprintf_s(buffer, len, fmt.c_str(), args);
	OutputDebugStringW(buffer);
	
	free(buffer);
}
