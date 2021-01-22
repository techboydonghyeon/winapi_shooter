#pragma once
#include "Enemy.h"
class Turtle :
	public Enemy
{
private:
	GdiImg* sprint;				//�̹��� ã�� ����
public:
	Turtle();
	Turtle(ObjectID ID_, int x_, int y_);
	virtual ~Turtle();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void InRange();

	//�̹��� �ٲ��ٶ� �ʿ��� �Լ�
	virtual void ChangeImg();

	virtual bool IsAlive()const { return isAlive; }
	virtual bool IsSameID(ObjectID ID_) const { return ID == ID_ ? true : false; }

};

