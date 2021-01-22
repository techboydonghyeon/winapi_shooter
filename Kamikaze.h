#pragma once
#include "Enemy.h"
class Kamikaze :
	public Enemy
{
private:
	GdiImg* sprint;				//�̹��� ã�� ����
	GdiImg* sprint1;			//�̹��� ã�� ����
	//ī��ī�� �̹��� enum��
	enum KAMIIMAGE
	{
		IDLE,					//������ ���� ��
		WALK,					//�ȱ�
		DASH,					//�뽬
		ATTACK,					//����
		PRECISION,				//ġ��Ÿ�� ���
		DEATH					//����
	};
	KAMIIMAGE kamiImage;
private:
	int dashCount;				//�뽬�� �� �α�
	int frameCount;			//���ǵ常ŭ ��� �̵�����
	bool dash;					//�뽬�ϴ°�?

	char str[256];				//�׳� ��ǥ Ȯ�ο� ����
	char str1[256];				//�׳� ��ǥ Ȯ�ο� ����

public:
	Kamikaze();
	Kamikaze(ObjectID ID_, int x_, int y_);
	virtual ~Kamikaze();

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

