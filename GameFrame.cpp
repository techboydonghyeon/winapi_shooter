#include "stdafx.h"
#include "WinProc.h"
#include "Engine.h"
#include "SystemInfo.h"
//-----------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	WinProc(hInstance, nCmdShow);
	ENGINE->Init();
	ENGINE->MainLoop();
	ENGINE->Release();
	return (int)(_Message.wParam);
}
//-----------------------------------------------
