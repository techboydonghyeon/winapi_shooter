#pragma once

#include"gpimageManager.h"
#include "ObjectM.h"
#include "PhsyicsM.h"
#include "RenderM.h"
#include "DATA.h"

#ifndef __MANAGER_MACRO_H__
#define __MANAGER_MACRO_H__
/*----------------------------------------------------

       ���� �� Ű�Է� �̱����� SystemInfo ����

-----------------------------------------------------*/

// �̱��� ��ũ��
#define IMAGE gpimageManager::GetInstance()
#define OBJECT ObjectM::GetInstance()
#define RENDER RenderM::GetInstance()
#define PHSYICS PhsyicsM::GetInstance()
#define DATA Data::GetInstance()

#include "Camera.h"
// ī�޶� �̱��� ��ũ�� 
#define CAMERA Camera::GetInstance()


//----------------------------------------------------


#endif // !__MANAGER_MACRO_H__