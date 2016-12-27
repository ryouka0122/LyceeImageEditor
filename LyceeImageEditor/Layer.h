#ifndef __LAYER_HEADER__
#define __LAYER_HEADER__

#include "includes.h"

#include "GraphicType.h"

namespace lycee {

	class Layer {
	protected:
		~Layer() { }
	public:
		virtual int width() const = 0;
		virtual int height() const = 0;

	public:
		virtual void move(int dx, int dy) = 0;
		virtual void moveTo(int x, int y) = 0;
		
		virtual bool hittest(int x, int y) = 0;

		virtual void render(Gdiplus::Graphics &g) =0;

		virtual PointI getLocation() const = 0;

	};

}	// lycee
#endif	// __LAYER_HEADER__