#pragma once
#include "Object.h"
class Enemy : public Object
{
protected:
	float speed;
	float range;
	float width;
	float height;
	bool discover;
	bool isLeft;

	//int damage;
public:
	Enemy();
	virtual ~Enemy();
	void getAngle(void);

	//int getDamage() { return damage; }
};

