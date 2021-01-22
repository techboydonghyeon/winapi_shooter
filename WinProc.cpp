#include "stdafx.h"
#include "WinProc.h"
#include "Engine.h"
#include "SystemInfo.h"
//-----------------------------------------------
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//-----------------------------------------------
WinProc::WinProc()
{
}
//-----------------------------------------------
WinProc::~WinProc()
{
	UnregisterClass(_WIN_NAME, _hInstance);
}
//-----------------------------------------------

WinProc::WinProc(HINSTANCE hInstance_, int nCmdShow_)
{

	_hInstance = hInstance_;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = _hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = _WIN_NAME;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&WndClass);

	_hWnd = CreateWindow(_WIN_NAME, _WIN_NAME, WS_OVERLAPPEDWINDOW,
		_WINSTARTX, _WINSTARTY, _WINSIZEX, _WINSIZEY,
		NULL, (HMENU)NULL, _hInstance, NULL);

	ShowWindow(_hWnd, nCmdShow_);

	RECT rc = { 0, 0, _WINSIZEX, _WINSIZEY };

	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, CS_HREDRAW | CS_VREDRAW, false);

	//위 렉트 정보로 윈도우 클라이언트 사이즈 세팅
	SetWindowPos(_hWnd, NULL, _WINSTARTX, _WINSTARTY, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
//-----------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_CREATE:
		_hWnd = hWnd;
		break;
	case WM_MOUSEMOVE:
		_mouse.x = LOWORD(lParam);
		_mouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
//-----------------------------------------------