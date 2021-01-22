#include "stdafx.h"
#include "Bomb.h"


Bomb::Bomb(ObjectID ID_, int x_, int y_)
{
	ID = ID_, x = x_, y = y_;
	OBJECT->CreateObject(this, I_BOMB);
	isAlive = true;
	isPickUp = false;
	bomb = HEAVY_BOMB;
	imageRc = {(LONG)x, (LONG)y,100, 100};
}


Bomb::~Bomb()
{
}

void Bomb::Init()
{
}

void Bomb::Update()
{
	this->ImageFind(bomb);

	hitBox=imageRc = { (LONG)x, (LONG)y,
		(LONG)(x + bombImage->GetGdiInfo()->imgWidth),
		(LONG)(y + bombImage->GetGdiInfo()->imgHeight) };
	

}

void Bomb::Render()
{
	Gdiplus::Graphics gm(_mdc);	//그릴때 필요한 거
	//CAMERA->CAM_FRAMERENDER(&gm, bombImage, x, y, 5);
	if (CAMERA->CAM_FRAMERENDER_BOOL(&gm, bombImage, x, y, 5)
		&& isPickUp)
	{
		isAlive = false;
	}

}

void Bomb::Release()
{
}

void Bomb::ImageFind(BOMB bomb_)
{
	bomb = bomb_;

	if (!isPickUp)
	{
		switch (bomb_)
		{
		case LIHGT_BOMB:
			bombImage = IMAGE->findImg("spr_bomb_light_0-sheet");
			break;
		case MIDIUM_BOMB:
			bombImage = IMAGE->findImg("spr_bomb_medium_0-sheet");
			break;
		case HEAVY_BOMB:
			bombImage = IMAGE->findImg("spr_bomb_heavy_0-sheet");
			break;

		}
	}
	else 
	{
		switch (bomb_)
		{
		case LIHGT_BOMB:
			bombImage = IMAGE->findImg("spr_pickup_light_0-sheet");
			break;
		case MIDIUM_BOMB:
			bombImage = IMAGE->findImg("spr_pickup_medium_0-sheet");
			break;
		case HEAVY_BOMB:
			bombImage = IMAGE->findImg("spr_pickup_heavy");
			break;

		}
	}
}


void Bomb::IsPickUp()
{
	isPickUp = true;
}

