#pragma once
#include "Object.h"
class Player :
	public Object
{
	//�÷��̾��� ����� ��������� ���⿡
protected:
	float speed;		//�̵���
	float angle;		//�̵�����
	bool isRight;		//�ٶ󺸰��ִ¹���
public:
	Player();
	virtual ~Player();
};
