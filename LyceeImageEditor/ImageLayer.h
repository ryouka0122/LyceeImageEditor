#ifndef __IMAGE_LAYER__HEADER__
#define __IMAGE_LAYER__HEADER__

#include "includes.h"

#include "GraphicType.h"
#include "Layer.h"

namespace lycee {

	class ImageLayer : virtual public Layer {
	public:
		virtual ~ImageLayer();
		ImageLayer();

		virtual int width() const {
			return this->image ? this->image->GetWidth() : 0;
		}

		virtual int height() const {
			return this->image ? this->image->GetHeight() : 0;
		}

		virtual bool load(const tstring &path);

		virtual void move(int dx, int dy);
		virtual void move(const PointI &pt);

		virtual void moveTo(int x, int y);
		virtual void moveTo(const PointI &pt);

		virtual bool hittest(int x, int y);
		virtual bool hittest(const PointI &pt);

		virtual void render(Gdiplus::Graphics &g);

		virtual PointI getLocation() const {
			return this->pt;
		}

	private:
		Gdiplus::Bitmap *image;
		PointI pt;

		bool load0(const WCHAR *path);

	};

}	// lycee
#endif	// __IMAGE_LAYER__HEADER__