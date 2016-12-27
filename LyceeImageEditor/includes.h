#ifndef __INCLUDES_HEADER__
#define __INCLUDES_HEADER__

#include <Windows.h>

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include <varargs.h>

#include <cstdlib>
#include <locale>
#include <memory>	// std::auto_ptr

#include <fstream>

#include <map>
#include <list>
#include <string>

namespace lycee {
#if defined(_UNICODE) || defined(UNICODE)
	typedef wchar_t tchar;
	typedef std::basic_string<wchar_t> tstring;

#else
	typedef char tchar;
	typedef std::basic_string<char> tstring;

#endif
	typedef std::basic_string<wchar_t> lycee_string;

}	// lycee
#endif	// __INCLUDES_HEADER__