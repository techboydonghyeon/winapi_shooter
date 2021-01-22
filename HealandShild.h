#pragma once
#include "Item.h"




class HealandShild : public Item
{
private:
	GdiImg* ItemImage;
	HEAL_SHILID heal_shild;
	bool isPickUp;

	
public:
	HealandShild(ObjectID, int, int);
	~HealandShild();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void imageFind(HEAL_SHILID hs_);
	HEAL_SHILID GetItem() { return heal_shild; }
	void SetIsPickUp();
	void isAliveBool();
};

