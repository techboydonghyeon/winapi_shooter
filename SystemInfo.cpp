#include "stdafx.h"
#include "SystemInfo.h"
//-----------------------------------------------
// ������ â ���� ����
HWND _hWnd;
MSG  _Message;
POINT _mouse;

//-----------------------------------------------
// GDI+ ��ū 
ULONG_PTR           gpToken;
GdiplusStartupInput gpInput;