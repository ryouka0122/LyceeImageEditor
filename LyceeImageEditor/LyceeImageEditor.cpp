#include "LyceeImageEditor.h"

lycee::LyceeImageEditor::~LyceeImageEditor() {
	this->release();
}

lycee::LyceeImageEditor::LyceeImageEditor()
	: initialized(false),
	hInstance(NULL),
	mainAtom(INVALID_ATOM),
	hWnd(NULL),
	gdiplusToken(0),
	gsi()
{
	// ƒƒP[ƒ‹Ý’è
	setlocale(LC_ALL, "japanese");

}

bool lycee::LyceeImageEditor::initialize(HINSTANCE hInstance) {
	if (this->initialized) {
		return true;
	}
	WNDCLASSEX wcex = {0};
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(wcex);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = lycee::LyceeImageEditor::globalWndProc;
	wcex.lpszClassName = TEXT("lycee.LyceeImageEditor");
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	ATOM atom = RegisterClassEx(&wcex);
	
	if(atom==INVALID_ATOM) {
		return false;
	}
	Gdiplus::GdiplusStartup(&gdiplusToken, &gsi, NULL);
	this->mainAtom = atom;
	this->hInstance = hInstance;
	this->initialized = true;
	return true;
}

void lycee::LyceeImageEditor::execute(int nCmdShow) {
	MSG msg;
	BOOL bRes;
	if (this->initialized == false) {
		return;
	}

	this->hWnd = CreateWindowEx(0, MAKEINTATOM(this->mainAtom),
		TEXT("LyceeImageEditor"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, this->hInstance, NULL);
	if (!IsWindow(this->hWnd)) {
		return;
	}

	ShowWindow(this->hWnd, nCmdShow);
	UpdateWindow(this->hWnd);

	while (true) {
		bRes = GetMessage(&msg, NULL, 0, 0);
		if (bRes <= 0) break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return;
}

void lycee::LyceeImageEditor::release() {
	if (this->initialized == false) {
		return;
	}
	if (IsWindow(this->hWnd)) {
		DestroyWindow(this->hWnd);
	}
	if (this->mainAtom!=INVALID_ATOM) {
		UnregisterClass(MAKEINTATOM(this->mainAtom), this->hInstance);
	}
	if (this->gdiplusToken) {
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
	this->hInstance = NULL;
	this->mainAtom = INVALID_ATOM;
	this->hWnd = NULL;
	this->initialized = false;
	return;
}

LRESULT lycee::LyceeImageEditor::globalWndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	return LRESULT();
}
