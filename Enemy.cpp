#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}


void Enemy::getAngle()
{
	float deltaX = 0, deltaY = 0;
	float _angle = 0;
	float distance = 0;
	deltaX = OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().x - x;
	deltaY = OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().y - y;
	distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
	_angle = acosf(deltaX / distance);
	if (OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().y > y)
	{
		_angle = 2 * 3.141592 - _angle;
		if (_angle > 2 * 3.141592)
		{
			_angle -= 2 * 3.141592;
		}
	}
	angle = _angle;
}
