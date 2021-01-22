#pragma once
#include "stdafx.h"
#ifndef __WINDOWS__
#define __WINDOWS__
//-----------------------------------------------
// 윈도우 인스턴스 전역
static HINSTANCE _hInstance;
//-----------------------------------------------
// 키 클래스 싱글턴
#include "KeyInput.h"
#define INPUT KeyInput::GetInput()
//-----------------------------------------------
// 엔진 클래스 싱글턴
#include "Engine.h"
#define ENGINE Engine::GetInstance()
//-----------------------------------------------
#include "Time.h"
// 타임 클래스 싱글턴
#define TIME Time::GetInstance()
// 델타 타임 반환
#define DeltaTime Time::GetInstance()->GetDeltaTime()
//-----------------------------------------------
// 마우스 구조체
//struct MOUSE
//{
//	double x;
//	double y;
//	MOUSE() : x(0), y(0)
//	{
//	}
//// 전역 마우스 변수
//}static _mouse;
extern POINT _mouse;

//-----------------------------------------------
// 윈도우 창 생성 정보
extern HWND _hWnd;
extern MSG  _Message;

// GDI+ 토큰
extern ULONG_PTR           gpToken;
extern GdiplusStartupInput gpInput;

//-----------------------------------------------
// 윈도우창 정보
// 형(type) const 이므로 수정 불가능.
//static const LPCSTR _WIN_NAME  = (LPCSTR)L"Relic Hunters";
//static const int _WINSTARTX = 200;
//static const int _WINSTARTY = 100;
//static const int _WINSIZEX  = 1400;
//static const int _WINSIZEY  = 800;
//static double currentTime = 0;

//-----------------------------------------------
#endif // !__WINDOWS__

