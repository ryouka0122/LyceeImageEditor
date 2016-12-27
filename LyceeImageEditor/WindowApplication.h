#ifndef __WINDOW_APPLICATION__HEADER__
#define __WINDOW_APPLICATION__HEADER__

#include "includes.h"

namespace lycee {

	class WindowApplication
	{
	public:
		WindowApplication(HINSTANCE hInstance, const lycee_string &appName);
		virtual ~WindowApplication();

	public:
		virtual void initialize();
		virtual int execute();
		virtual void release();



	protected:
		ATOM getApplicationAtom();

		HWND createApplicationWindow(const lycee_string & title, RECT rect, HWND hParent, HMENU hMenu);

	private:
		HINSTANCE hInstance;
		ATOM appAtom;

		void makeAtom(HINSTANCE hInstance, const lycee_string &appName);
		void releaseAtom();

	public:
		static WindowApplication *application;
		static LRESULT CALLBACK applicationProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
	};

}	// lycee
#endif	// __WINDOW_APPLICATION__HEADER__