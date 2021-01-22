#pragma once
#include "Enemy.h"
class Turtle :
	public Enemy
{
private:
	GdiImg* sprint;				//이미지 찾기 변수
public:
	Turtle();
	Turtle(ObjectID ID_, int x_, int y_);
	virtual ~Turtle();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void InRange();

	//이미지 바꿔줄때 필요한 함수
	virtual void ChangeImg();

	virtual bool IsAlive()const { return isAlive; }
	virtual bool IsSameID(ObjectID ID_) const { return ID == ID_ ? true : false; }

};

