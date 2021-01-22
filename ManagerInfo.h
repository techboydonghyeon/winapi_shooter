#pragma once
//-----------------------------------------------
/*
해당 헤더를 사용하는 클래스
매니저 클래스 : ObjectM
매니저 클래스 : PhsyicsM
매니저 클래스 : RenderM
매니저 클래스 : SceneM
*/
//-----------------------------------------------
#ifndef __MANAGER_INFO__
#define __MANAGER_INFO__
//-----------------------------------------------
// 렌더 관리자
extern HDC  _hdc;
extern HDC  _mdc;

#include "gpimageManager.h"
using namespace Gdiplus;
//Gdiplus::Graphics drawer(_mdc);

//-----------------------------------------------
#endif // !__MANAGER_INFO__
