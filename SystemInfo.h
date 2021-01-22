#pragma once
#include "stdafx.h"
#ifndef __WINDOWS__
#define __WINDOWS__
//-----------------------------------------------
// ������ �ν��Ͻ� ����
static HINSTANCE _hInstance;
//-----------------------------------------------
// Ű Ŭ���� �̱���
#include "KeyInput.h"
#define INPUT KeyInput::GetInput()
//-----------------------------------------------
// ���� Ŭ���� �̱���
#include "Engine.h"
#define ENGINE Engine::GetInstance()
//-----------------------------------------------
#include "Time.h"
// Ÿ�� Ŭ���� �̱���
#define TIME Time::GetInstance()
// ��Ÿ Ÿ�� ��ȯ
#define DeltaTime Time::GetInstance()->GetDeltaTime()
//-----------------------------------------------
// ���콺 ����ü
//struct MOUSE
//{
//	double x;
//	double y;
//	MOUSE() : x(0), y(0)
//	{
//	}
//// ���� ���콺 ����
//}static _mouse;
extern POINT _mouse;

//-----------------------------------------------
// ������ â ���� ����
extern HWND _hWnd;
extern MSG  _Message;

// GDI+ ��ū
extern ULONG_PTR           gpToken;
extern GdiplusStartupInput gpInput;

//-----------------------------------------------
// ������â ����
// ��(type) const �̹Ƿ� ���� �Ұ���.
//static const LPCSTR _WIN_NAME  = (LPCSTR)L"Relic Hunters";
//static const int _WINSTARTX = 200;
//static const int _WINSTARTY = 100;
//static const int _WINSIZEX  = 1400;
//static const int _WINSIZEY  = 800;
//static double currentTime = 0;

//-----------------------------------------------
#endif // !__WINDOWS__

