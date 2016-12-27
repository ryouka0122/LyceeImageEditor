#include "ImageLayer.h"

#include "Functions.h"
#include "StringUtil.h"

lycee::ImageLayer::~ImageLayer()
{
	delete image;
}

lycee::ImageLayer::ImageLayer()
	: image(nullptr)
	, pt(0, 0)
{
}

bool lycee::ImageLayer::load(const tstring & path)
{
	if (!lycee::Path::isExists(path)) {
		return false;
	}
	return load0(StringUtil::convert(path).c_str());
}

void lycee::ImageLayer::move(int dx, int dy)
{
	this->pt.x += dx;
	this->pt.y += dy;
}

void lycee::ImageLayer::move(const PointI & pt)
{
	this->pt += pt;
}

void lycee::ImageLayer::moveTo(int x, int y)
{
	this->pt.x = x;
	this->pt.y = y;
}

void lycee::ImageLayer::moveTo(const PointI & pt)
{
	this->pt = pt;
}

bool lycee::ImageLayer::hittest(int x, int y)
{
	int ix = x - this->pt.x;
	int iy = y - this->pt.y;
	if (ix < 0 || this->width() <= ix) {
		return false;
	}
	if (iy < 0 || this->height() <= iy) {
		return false;
	}
	Gdiplus::Color c;
	this->image->GetPixel(ix, iy, &c);
	return (0xFF==c.GetAlpha());
}

bool lycee::ImageLayer::hittest(const PointI & pt)
{
	return this->hittest(pt.x, pt.y);
}

void lycee::ImageLayer::render(Gdiplus::Graphics & g)
{
	g.DrawImage(this->image, this->pt.x, this->pt.y);
}

bool lycee::ImageLayer::load0(const WCHAR * path)
{
	if (this->image) {
		delete this->image;
	}
	this->image = new Gdiplus::Bitmap(path);
	return true;
}
