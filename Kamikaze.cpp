#include "stdafx.h"
#include "Kamikaze.h"


Kamikaze::Kamikaze()
{
}

Kamikaze::Kamikaze(ObjectID ID_, int x_, int y_)
{
	hp = 10;
	damage = 10;

	//카미카제 id를 받아서 카테고리를 찾아 에너미 벡터에 푸쉬백으로 넣어 x, y 좌표에 카미카제 생성
	ID = ID_, x = x_, y = y_;
	isAlive = true;
	dashCount = 0;
	frameCount = 0;
	angle = 0.f;
	speed = 25.f;
	range = 1000.f;
	width = 114.f;
	height = 94.f;
	imageRc = { (LONG)(x - width / 2), (LONG)(y - height / 2),(LONG)(x + width / 2), (LONG)(y + height / 2) };
	dash = false;
	isLeft = false;
	discover = false;
	OBJECT->CreateObject(this, ID);
	hitBox = imageRc;
}

Kamikaze::~Kamikaze()
{
}

void Kamikaze::Init()
{

}

void Kamikaze::Update()
{
	//=============================== 이미지 ==================================
	//오른쪽
	if (angle > 0 && angle <= 3.141592 / 2 || angle > 3 * 3.141592 / 2 && angle <= 2 * 3.141592)
	{
		isLeft = false;
	}
	//왼쪽
	if (angle > 3.141592 / 2 && angle <= 3 * 3.141592 / 2)
	{
		isLeft = true;
	}
	//상황에 맞는 이미지 찾기
	if (isLeft)
	{
		switch (kamiImage)
		{
		case Kamikaze::IDLE:
			sprint = IMAGE->findImg("spr_kamikaze_idle_0-sheet_left");
			break;
		case Kamikaze::WALK:
			sprint = IMAGE->findImg("spr_kamikaze_walk_0-sheet_left");
			break;
		case Kamikaze::DASH:
			sprint = IMAGE->findImg("spr_kamikaze_dash_fx_0-sheet_left");
			break;
		case Kamikaze::ATTACK:
			sprint = IMAGE->findImg("spr_kamikaze_attack_0-sheet_left");
			break;
		case Kamikaze::PRECISION:
			sprint = IMAGE->findImg("spr_kamikaze_precision2_0-sheet");
			break;
		case Kamikaze::DEATH:
			sprint = IMAGE->findImg("spr_kamikaze_death_0-sheet_left");
			break;
		default:
			break;
		}
		sprint1 = IMAGE->findImg("spr_kamikaze_dash_fx_0-sheet_left");
	}
	else
	{
		switch (kamiImage)
		{
		case Kamikaze::IDLE:
			sprint = IMAGE->findImg("spr_kamikaze_idle_0-sheet");
			break;
		case Kamikaze::WALK:
			sprint = IMAGE->findImg("spr_kamikaze_walk_0-sheet");
			break;
		case Kamikaze::DASH:
			sprint = IMAGE->findImg("spr_kamikaze_dash_fx_0-sheet");
			break;
		case Kamikaze::ATTACK:
			sprint = IMAGE->findImg("spr_kamikaze_attack_0-sheet");
			break;
		case Kamikaze::PRECISION:
			sprint = IMAGE->findImg("spr_kamikaze_precision2_0-sheet");
			break;
		case Kamikaze::DEATH:
			sprint = IMAGE->findImg("spr_kamikaze_death_0-sheet");
			break;
		default:
			break;
		}
		sprint1 = IMAGE->findImg("spr_kamikaze_dash_fx_0-sheet");
	}
	kamiImage = IDLE;
	//==========================================================================

	//================================ 움직임 ===================================
	dashCount++;

	this->InRange();
	//대쉬하는 텀을 줌
	if (dashCount % 200 == 0)
	{
		//대쉬하는 순간에 플레이어 앵글값을 받아옴
		this->getAngle();
		if (discover)
		{
			dash = true;
		}
		//대쉬카운트의 숫자가 너무 커지지 않도록 함
		if (dashCount >= 2000)
		{
			dashCount = 0;
		}
	}


	//대쉬 할때
	if (dash)
	{
		x += cosf(angle) * speed;
		y += -sinf(angle) * speed;
		frameCount++;
		kamiImage = ATTACK;
		//카미카제가 순간이동하는 것처럼 안보이게 할라고 넣어줌
		//자연스럽게 대쉬하는 모습으로 보이도록
		//이동거리만큼 몇번 가는 것임
		//스피드만큼 6번 이동함
		if (frameCount == 6)
		{
			dash = false;
			frameCount = 0;
		}
	}
	imageRc = { (LONG)(x - width / 2), (LONG)(y - height / 2),(LONG)(x + width / 2), (LONG)(y + height / 2) };
	hitBox = imageRc;
	//==========================================================================
	sprintf(str, "x 좌표: %f", x);
	sprintf(str1, "angle : %f", angle);
}

void Kamikaze::Render()
{
	Gdiplus::Graphics gm(_mdc);

	//대쉬할때 뒤에 효과(대쉬 이미지) 넣기(그림자 같은 이미지)
	if (kamiImage == ATTACK)
	{
		CAMERA->CAM_FRAMERENDER(&gm, sprint1, cosf(3.141592 + angle) * 20 + x, -sinf(3.141592 + angle) * 20 + y, 4);
	}
	//카미카제의 모든 이미지
	CAMERA->CAM_FRAMERENDER(&gm, sprint, x, y, 7);


	TextOut(_mdc, 0, 100, str, strlen(str));
	TextOut(_mdc, 0, 200, str1, strlen(str1));
}

void Kamikaze::Release()
{
}

void Kamikaze::InRange()
{
	float deltaX = 0, deltaY = 0;
	float distance = 0;
	deltaX = OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().x - x;
	deltaY = OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().y - y;
	distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
	if (distance < range)
	{
		discover = true;
	}
}

void Kamikaze::ChangeImg()
{
	//sprint = IMAGE->findImg("shotgun_0");
}