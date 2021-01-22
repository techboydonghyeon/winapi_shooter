#pragma once
#include "Item.h"



class Bomb : public Item
{
private:
	GdiImg* bombImage;
	BOMB bomb;
	bool isPickUp;
public:
	Bomb(ObjectID ID_, int x_, int y_);
	~Bomb();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void ImageFind(BOMB bomb_);
	void IsPickUp();
	BOMB GetBomb() { return bomb; }
};

