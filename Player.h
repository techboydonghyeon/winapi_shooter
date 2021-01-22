#pragma once
#include "Object.h"
class Player :
	public Object
{
	//플레이어의 공통된 멤버변수는 여기에
protected:
	float speed;		//이동값
	float angle;		//이동방향
	bool isRight;		//바라보고있는방향
public:
	Player();
	virtual ~Player();
};
