#include "stdafx.h"
#include "Object.h"
using namespace ObjectInfo;
Object::Object() :
	ID(END_OBJECTID),   
	x(0),
	y(0),
	imageRc({0,0,0,0}),
	hitBox({0,0,0,0}),
	isAlive(false)
{	
}

void Object::Dameged(int amount_)
{
	this->hp -= amount_;

	if (this->hp < 0)
	{
		isAlive = false;
	}
}

void Object::Dameged(int amount_, int absolute_)
{
	this->hp -= amount_ + absolute_;

	if (this->hp < 0)
	{
		isAlive = false;
	}
}