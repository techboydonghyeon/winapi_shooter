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
 Ÿ�� �̹��� ������
**************************************************/
void Camera::CAM_RENDER(Gdiplus::Graphics* gm, string ID, int x_, int y_)
{
	IMAGE->render(
		gm,
		ID.c_str(),    // ������ �� Ÿ�� �̹���
		(int)((x_ -= rc.left)* zoom), // LEFT
		(int)((y_ -= rc.top) * zoom)   // TOP ���� �����
	);
}

void Camera::CAM_RENDER(Gdiplus::Graphics* gm, GdiImg* MEME, int x_, int y_)
{
	IMAGE->render(
		gm,
		MEME->GetGimg(),    // ������ �� Ÿ�� �̹���
		(int)((x_ -= rc.left)* zoom), // LEFT
		(int)((y_ -= rc.top) * zoom)   // TOP ���� �����
	);
}
void Camera::CAM_RENDER(string ID, int x_, int y_)
{
	IMAGE->render(
		ID.c_str(),    // ������ �� Ÿ�� �̹���
		(int)((x_ -= rc.left)* zoom), // LEFT
		(int)((y_ -= rc.top) * zoom)   // TOP ���� �����
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
// 03/05 �߰�(ȸ������)
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
// Ŭ���� �������� Update���� ��� ȣ��
// ī�޶� ��ġ�� ����� ������.
void Camera::SettingCamera(int xFromTarget_, int yFromTarget_)
{
	
	x = xFromTarget_ + ((_mouse.x + rc.left) - xFromTarget_)/4;					// ī�޶� x ��ǥ <-- ���콺 x��ǥ
	y = yFromTarget_ + ((_mouse.y + rc.top) - yFromTarget_)/4;					// ī�޶� y ��ǥ <-- ���콺 y��ǥ

	rc = { x - _WINSIZEX / 2, y - _WINSIZEY / 2 ,
		x + _WINSIZEX/2, y+ _WINSIZEY/2 };		//ķ �׷��ֱ�	

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
