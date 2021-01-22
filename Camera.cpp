#include "stdafx.h"
#include "Camera.h"
#include "SystemInfo.h"

//---------------------------------------------------
SINGLETON_S(Camera)
//---------------------------------------------------
void Camera::Init()
{
	rc = { 0,0,_WINSIZEX,_WINSIZEY };
	x = 0;
	y = 0;
	zoom = 1.0f;
	check = false;
}
//---------------------------------------------------
/*************************************************
 타일 이미지 렌더링
**************************************************/
void Camera::CAM_RENDER(Gdiplus::Graphics* gm, string ID, int x_, int y_)
{
	IMAGE->render(
		gm,
		ID.c_str(),    // 렌더링 할 타겟 이미지
		(int)((x_ -= rc.left)* zoom), // LEFT
		(int)((y_ -= rc.top) * zoom)   // TOP 기준 드로잉
	);
}

void Camera::CAM_RENDER(Gdiplus::Graphics* gm, GdiImg* MEME, int x_, int y_)
{
	IMAGE->render(
		gm,
		MEME->GetGimg(),    // 렌더링 할 타겟 이미지
		(int)((x_ -= rc.left)* zoom), // LEFT
		(int)((y_ -= rc.top) * zoom)   // TOP 기준 드로잉
	);
}
void Camera::CAM_RENDER(string ID, int x_, int y_)
{
	IMAGE->render(
		ID.c_str(),    // 렌더링 할 타겟 이미지
		(int)((x_ -= rc.left)* zoom), // LEFT
		(int)((y_ -= rc.top) * zoom)   // TOP 기준 드로잉
	);
}
void Camera::CAM_FRAMERENDER(Gdiplus::Graphics * gm, GdiImg * gpimg, int x, int y, int delay)
{
	IMAGE->render(
		gm,
		gpimg,
		(int)((x -= rc.left)* zoom),
		(int)((y -= rc.top) * zoom),
		delay
	);
}
bool Camera::CAM_FRAMERENDER_BOOL(Gdiplus::Graphics * gm, GdiImg * gpimg, int x, int y, int delay)
{
	if (IMAGE->renderBool(
		gm,
		gpimg,
		(int)((x -= rc.left)* zoom),
		(int)((y -= rc.top) * zoom),
		delay
	))
	{
		return true;
	}
	else
	{
		return false;
	}

	
}
// 03/05 추가(회전렌더)
void Camera::CAM_RENDER(GdiImg * gpimg, int x, int y, float angle)
{
	IMAGE->render(
		gpimg,
		(int)((x -= rc.left)* zoom),
		(int)((y -= rc.top) * zoom),
		angle
	);
}



//---------------------------------------------------
void Camera::SettingCamera(CAMERA_SETTING TARGET_)
{
	setting = TARGET_;

	switch (TARGET_)
	{
	case Camera::TAGET:
		break;
	case Camera::FREE:
		break;
	default:
		break;
	}


}

//---------------------------------------------------
// 클래스 누군가의 Update에서 계속 호출
// 카메라 위치가 제대로 잡힌다.
void Camera::SettingCamera(int xFromTarget_, int yFromTarget_)
{
	
	x = xFromTarget_ + ((_mouse.x + rc.left) - xFromTarget_)/4;					// 카메라 x 좌표 <-- 마우스 x좌표
	y = yFromTarget_ + ((_mouse.y + rc.top) - yFromTarget_)/4;					// 카메라 y 좌표 <-- 마우스 y좌표

	rc = { x - _WINSIZEX / 2, y - _WINSIZEY / 2 ,
		x + _WINSIZEX/2, y+ _WINSIZEY/2 };		//캠 그려주기	

}

//---------------------------------------------------
void Camera::ZoomFactor()
{
	if (INPUT->isToggle(VK_RBUTTON))
		zoom = 2.2f;
	else
		zoom = 1.0f;
}
//---------------------------------------------------

float Camera::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	float distance = sqrtf(x * x + y * y);
	float angle = acosf(x / distance);
	if (endY > startY)
	{
		angle = 2 * PI - angle;
		if (angle > 2 * PI) angle -= 2 * PI;
	}
	return angle;
}
