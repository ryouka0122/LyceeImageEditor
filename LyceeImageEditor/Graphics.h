#ifndef __GRAPHICS__HEADER__
#define __GRAPHICS__HEADER__

#include "includes.h"

namespace lycee {

	class Graphics {
	public:
		
		static Gdiplus::Image* LoadImage(const std::string &path);

	};

}
#endif	// __GRAPHICS__HEADER__