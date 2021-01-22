#pragma once
//--------------------------------------
#include "targetver.h"
//--------------------------------------
#define WIN32_LEAN_AND_MEAN          
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <string>
#include <fstream>
#include <iomanip>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
// 알고리즘 헤더
#include <algorithm>
#include <utility>
// 안정성
#include <assert.h>
// GDI PLUS 
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus")
using namespace std;
using namespace Gdiplus;
//--------------------------------------
// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
//--------------------------------------
#include "Useful.h"
#include "ManagerInfo.h"
#include "ObjectInfo.h"
#include "Management.h"
#include "Define.h"

#include "Object.h"
#include "Tile.h"
#include "Pinky.h"
#include "Kamikaze.h"
#include "Turtle.h"
#include "Gun.h"
#include "Bomb.h"
#include "HealandShild.h"


//--------------------------------------
// 매니저 클래스
#include "RenderM.h"
#include "ObjectM.h"
#include "PhsyicsM.h"
#include "SceneM.h"

#include "ManagerMacro.h"
//--------------------------------------


#define PI 3.141592

//-----------------------------------------------
// 윈도우창 정보
// 형(type) const 이므로 수정 불가능.
static const LPCSTR _WIN_NAME = (LPCSTR)L"Relic Hunters";
static const int _WINSTARTX = 200;
static const int _WINSTARTY = 100;
static const int _WINSIZEX = 1400;
static const int _WINSIZEY = 800;
static double currentTime = 0;
