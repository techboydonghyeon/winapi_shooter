#pragma once
#include "Item.h"



class Gun : public Item
{
private:
	GdiImg* gunImage;
	GUN gun;
	bool isPickUp;

public:
	Gun(ObjectID ID_, int x_, int y_);
	~Gun();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void imageFind(GUN gun_);
	//GUN GetGun() { return gun; }
	ObjectID GetGun();
	void SetGun(GUN gun_) { gun = gun_; }
	void SetIsPickUp();
	void isAliveBool();

	virtual bool IsAlive()const { return isAlive; }
	virtual bool IsSameID(ObjectID ID_) const { return ID == ID_ ? true : false; }
};

