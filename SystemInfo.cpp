#include "stdafx.h"
#include "SystemInfo.h"
//-----------------------------------------------
// 윈도우 창 생성 정보
HWND _hWnd;
MSG  _Message;
POINT _mouse;

//-----------------------------------------------
// GDI+ 토큰 
ULONG_PTR           gpToken;
GdiplusStartupInput gpInput;