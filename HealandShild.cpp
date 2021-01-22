#include "stdafx.h"
#include "HealandShild.h"


HealandShild::HealandShild(ObjectID ID_, int x_, int y_)
{
	ID = ID_,   x = x_, y = y_;
	isPickUp = false;
	isAlive = true;
	heal_shild = SHILD;
	imageRc = { (LONG)x, (LONG)y, (LONG)100, (LONG)100 };
	hitBox = imageRc;
	OBJECT->CreateObject(this, I_HEAL_SHILD);
}


HealandShild::~HealandShild()
{
}

void HealandShild::Init()
{
}

void HealandShild::Update()
{
	this->imageFind(heal_shild);

	hitBox = imageRc = { (LONG)x, (LONG)y,
	(LONG)(x + ItemImage->GetGdiInfo()->imgWidth),
		(LONG)(y + ItemImage->GetGdiInfo()->imgHeight) };

}

void HealandShild::Render()
{
	Gdiplus::Graphics gm(_mdc);	

	CAMERA->CAM_FRAMERENDER(&gm, ItemImage, x, y, 5);

}

void HealandShild::Release()
{
}

void HealandShild::imageFind(HEAL_SHILID hs_)
{
	heal_shild = hs_;


	switch (heal_shild)
	{
	case HEAL:
		ItemImage = IMAGE->findImg("spr_pickup_healthBig_0-sheet");
		break;
	case SHILD:
		ItemImage = IMAGE->findImg("spr_pickup_shield_0-sheet");
		break;
	}
	

}

void HealandShild::SetIsPickUp()
{
	isPickUp = true;
}

void HealandShild::isAliveBool()
{
	isAlive = false;
}



