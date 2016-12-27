#include "procedure.h"
#include "Functions.h"
#include "ImageLayer.h"

lycee::ImageLayer *layer;

std::basic_string<TCHAR> path = TEXT("E:\\Projects\\lycee\\workspace\\LyceeImageEditor\\01.png");

LRESULT CALLBACK lycee::mainWndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) {
	PAINTSTRUCT ps;

	switch (uMsg) {
	case WM_CREATE:
		layer = new lycee::ImageLayer();
		layer->load(path);
		lycee::Log::debug("width : %d\n", layer->width());
		lycee::Log::debug("height : %d\n", layer->height());
		return 0;

	case WM_PAINT:
		if (HDC hdc = BeginPaint(hWnd, &ps)) {
			Gdiplus::Graphics g(hdc);
			layer->render(g);
			EndPaint(hWnd, &ps);
		}
		return 0;
	case WM_KEYUP:
		
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}