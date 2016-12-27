#include "WindowApplication.h"



lycee::WindowApplication::WindowApplication(
	HINSTANCE hInstance,
	const lycee::lycee_string &appName)
	: appAtom(INVALID_ATOM), hInstance(NULL)
{
	makeAtom(hInstance, appName);
}

lycee::WindowApplication::~WindowApplication()
{
	this->release();
}

ATOM lycee::WindowApplication::getApplicationAtom()
{
	return this->appAtom;
}

HWND lycee::WindowApplication::createApplicationWindow(
	const lycee_string & title, RECT rect, HWND hParent, HMENU hMenu)
{
	return CreateWindowEx(0, MAKEINTATOM(appAtom), title.c_str(), WS_OVERLAPPEDWINDOW,
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		hParent, hMenu, hInstance, this);
}

void lycee::WindowApplication::makeAtom(HINSTANCE hInstance, const lycee_string & appName)
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(wcex);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = lycee::WindowApplication::applicationProc;
	wcex.lpszClassName = appName.c_str();
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	this->appAtom = RegisterClassEx(&wcex);

	if (this->appAtom == INVALID_ATOM) {
		this->hInstance = hInstance;
	}
}

void lycee::WindowApplication::releaseAtom()
{
	UnregisterClass(MAKEINTATOM(this->appAtom), this->hInstance);
	this->appAtom = INVALID_ATOM;
	this->hInstance = NULL;
}


lycee::WindowApplication *lycee::WindowApplication::application = NULL;

LRESULT lycee::WindowApplication::applicationProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{

	return DefWindowProc(hWnd, uMsg, wp, lp);
}

