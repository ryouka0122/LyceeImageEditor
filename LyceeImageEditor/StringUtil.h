#ifndef __STRING_UTIL__HEADER__
#define __STRING_UTIL__HEADER__

#include "includes.h"

namespace lycee {

	class StringUtil
	{
	public:
		template<typename _Ch>
		static lycee_string convert(const std::basic_string<_Ch> &str) {
			return lycee_string();
		}
		
		template<>
		static lycee_string convert<char>(const std::basic_string<char> &str) {
			lycee_string result;
			size_t size = 0;
			wchar_t *buf = 0;

			mbstowcs_s(&size, buf, 0, str.c_str(), str.size());
			
			if (size > 1) {
				buf = (wchar_t*)malloc(sizeof(wchar_t)*size);
				memset(buf, 0, sizeof(wchar_t)*size);
				mbstowcs_s(&size, buf, size, str.c_str(), str.size());
				result.assign(buf);
				free(buf);
			}
			return result;
		}

		template<>
		static lycee_string convert<wchar_t>(const std::basic_string<wchar_t> &str) {
			return str;
		}
	};

}	// lycee
#endif	// __STRING_UTIL__HEADER__