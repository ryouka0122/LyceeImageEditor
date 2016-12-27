#ifndef __LYCEE_IMAGE_EDITOR__HEADER__
#define __LYCEE_IMAGE_EDITOR__HEADER__

#include "includes.h"

namespace lycee {

	class LyceeImageEditor {
	public:
		virtual ~LyceeImageEditor();
		LyceeImageEditor();

		virtual bool initialize(HINSTANCE hInstance);
		virtual void execute(int nCmdShow);
		virtual void release();

		static LRESULT CALLBACK globalWndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
	private:
		bool initialized;
		HINSTANCE hInstance;
		ATOM mainAtom;
		HWND hWnd;

		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartupInput gsi;
	};
	
}	// lycee
#endif	// __LYCEE_IMAGE_EDITOR__HEADER__