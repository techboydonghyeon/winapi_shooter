#include "stdafx.h"
#include "Turtle.h"


Turtle::Turtle()
{
}

Turtle::Turtle(ObjectID ID_, int x_, int y_)
{
	hp = 10;
	damage = 10;


	ID = ID_, x = x_, y = y_;
	isAlive = true;
	angle = 0.f;
	speed = 2.f;
	range = 600.f;
	width = 114.f;
	height = 94.f;
	imageRc = { (LONG)(x - width / 2), (LONG)(y - height / 2),(LONG)(x + width / 2), (LONG)(y + height / 2) };
	isLeft = false;
	discover = false;
	sprint = IMAGE->findImg("spr_duck2_idle_0-sheet");
	OBJECT->CreateObject(this, ID);

	hitBox = imageRc;
}


Turtle::~Turtle()
{
}

void Turtle::Init()
{
}

void Turtle::Update()
{
	this->getAngle();
	this->InRange();
	if (discover)
	{
		x += cosf(angle) * speed;
		y += -sinf(angle) * speed;
	}
	imageRc = { (LONG)(x - width / 2), (LONG)(y - height / 2),(LONG)(x + width / 2), (LONG)(y + height / 2) };
	hitBox = imageRc;
}

void Turtle::Render()
{
	Gdiplus::Graphics gm(_mdc);

	//카미카제의 모든 이미지
	CAMERA->CAM_FRAMERENDER(&gm, sprint, x, y, 7);
}

void Turtle::Release()
{
}

void Turtle::InRange()
{
	float deltaX = 0, deltaY = 0;
	float distance = 0;
	deltaX = OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().x - x;
	deltaY = OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().y - y;
	distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
	if (distance < range && distance > 100)
	{
		discover = true;
	}
	if(distance <= 100)
	{
		discover = false;
	}
}

void Turtle::ChangeImg()
{
}
