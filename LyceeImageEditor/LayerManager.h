#ifndef __LAYER_MANAGER__HEADER__
#define __LAYER_MANAGER__HEADER__

#include "includes.h"

#include "Layer.h"
#include "ImageLayer.h"

namespace lycee {
	
	class LayerManager {
	public:
		static Layer* CreateImageLayer();

		static Layer* LoadImageFile(const tstring &path);

	};

}	// lycee
#endif	// __LAYER_MANAGER__HEADER__