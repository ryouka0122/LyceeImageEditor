#ifndef __FUNCTIONS__HEADER__
#define __FUNCTIONS__HEADER__

#include "includes.h"

namespace lycee {
	class Log {
	private:

	public:
		static void debug(std::string fmt, ...);
		static void debug(std::wstring fmt, ...);
	};

	class Path {
	public:
		static bool isExists(const std::string &path);
		static bool isExists(const std::wstring &path);

	};


}	// lycee
#endif	// __FUNCTIONS__HEADER__