#include "stdafx.h"
#include "Gun.h"


Gun::Gun(ObjectID ID_, int x_, int y_)
{
	ID = ID_, x = x_, y = y_;
	isAlive = true;
	isPickUp = false;
	gun = MACHINEGUN;
	imageRc = { (LONG)x, (LONG)y, (LONG)x+100, (LONG)y+100 };
	hitBox = imageRc;
	OBJECT->CreateObject(this, I_GUN);
}

Gun::~Gun()
{
}

void Gun::Init()
{
}

void Gun::Update()
{
	this->imageFind(gun);


	hitBox = imageRc = { (LONG)x, (LONG)y,
	(LONG)(x +gunImage->GetGdiInfo()->imgWidth),
		(LONG)(y + gunImage->GetGdiInfo()->imgHeight) };

}

void Gun::Render()
{
	Gdiplus::Graphics gm(_mdc);
	CAMERA->CAM_RENDER(&gm, gunImage, x, y);
}

void Gun::Release()
{
}

void Gun::imageFind(GUN gun_)
{
	gun = gun_;
	
	switch (gun)
	{
	case PISTOL:
		gunImage = IMAGE->findImg("pistol_0");
		break;
	case SHOTGUN:
		gunImage = IMAGE->findImg("shotgun_0");
		break;
	case MACHINEGUN:
		gunImage = IMAGE->findImg("machinegun_0");
		break;
	}

}

ObjectID Gun::GetGun()
{
	switch (gun)
	{
	case PISTOL:
		return B_SINGLE;
		break;
	case SHOTGUN:
		return B_SHOTGUN;
		break;
	case MACHINEGUN:
		return B_AUTO;
		break;

	}
}

void Gun::SetIsPickUp()
{
	isPickUp = true;
}

void Gun::isAliveBool()
{
	isAlive = false;
}
