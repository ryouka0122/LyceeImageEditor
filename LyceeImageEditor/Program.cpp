#include "includes.h"
#include "procedure.h"

#define CLASS_NAME TEXT("LyceeImageEditor")
#define WINDOW_TITLE TEXT("LyceeImageEditor [1.0.0]")

ATOM Initialize(HINSTANCE hInstance) {
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = lycee::mainWndProc;
	wcex.lpszClassName = CLASS_NAME;
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	return RegisterClassEx(&wcex);
}

HWND MakeWindow(ATOM atom, HINSTANCE hInstance) {
	return CreateWindowEx(0, MAKEINTATOM(atom), WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	// ÉçÉPÅ[Éãê›íË
	setlocale(LC_ALL, "japanese");

	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gsi;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gsi, NULL);

	ATOM atom = Initialize(hInstance);
	if (atom == INVALID_ATOM) {
		return -1;
	}
	
	HWND hMainWindow = MakeWindow(atom, hInstance);	

	if (IsWindow(hMainWindow)) {
		ShowWindow(hMainWindow, nCmdShow);
		UpdateWindow(hMainWindow);
		
		MSG msg;
		BOOL bRes;
		while (true) {
			bRes = GetMessage(&msg, NULL, 0, 0);
			if (bRes <= 0) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);

	UnregisterClass(MAKEINTATOM(atom), hInstance);
	return 0;
}
