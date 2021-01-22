#pragma once

#include"gpimageManager.h"
#include "ObjectM.h"
#include "PhsyicsM.h"
#include "RenderM.h"
#include "DATA.h"

#ifndef __MANAGER_MACRO_H__
#define __MANAGER_MACRO_H__
/*----------------------------------------------------

       엔진 및 키입력 싱글톤은 SystemInfo 참고

-----------------------------------------------------*/

// 싱글톤 매크로
#define IMAGE gpimageManager::GetInstance()
#define OBJECT ObjectM::GetInstance()
#define RENDER RenderM::GetInstance()
#define PHSYICS PhsyicsM::GetInstance()
#define DATA Data::GetInstance()

#include "Camera.h"
// 카메라 싱글톤 매크로 
#define CAMERA Camera::GetInstance()


//----------------------------------------------------


#endif // !__MANAGER_MACRO_H__