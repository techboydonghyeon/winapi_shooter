#pragma once
#include"GpImage.h"

#define NUMWIDTH 20
#define DECREASESPEED 0.7f

class UI
{
private:
	//HP �ٿ� ���õ� ������
	GdiImg* pinkyFace[3];//��Ű �� �̹��� 3��
	GdiImg* shieldStamina;//����, ���¹̳�
	GdiImg* fonts[3];	//��Ʈ ������ ���� �ְ� ����

	int interval[3];	//�� ��Ʈ ���� �Ÿ�

	GdiImg* hpbar0;		//hp ��
	GdiImg* hpbar1;
	GdiImg* hpbar2;

	GdiImg* shbar0;		//���� ��
	GdiImg* shbar1;
	GdiImg* shbar2;

	GdiImg* stbar;		//���¹̳� ��
	GdiImg* stbars[2];	//���¹̳� ��1
	GdiImg* stbar_U;

	//�� ǥ��
	GdiImg* starbar;	//�� ���̴� ��

	//�� ǥ��
	GdiImg* guns[3];		//�� ������ �ֱ�
	GdiImg* ammobar;		//�Ѿ� ��
	GdiImg* ammobar2;		//�Ѿ� ��� ��



public:
	void Init();

	//3�ڸ��� ���� ����ϴ� �Լ� ��Ʈ�� 0,1,2 �� �ִ�. ���� ũ�� ������
	void ShowNumberH(Graphics* gm,int x, int y, int num,int font);
	//5�ڸ��� ���� ����ϴ� �Լ� ������ ���� ����
	void ShowNumberB(Graphics * gm, int x, int y, int num, int font);
	//hp ��,���� ��, ���¸ӳ� �� �� �����ִ� �Լ� �׳� ���̴� ��� �Է��ϸ� �ȴ�.
	void ShowHpBar(Graphics * gm, int hp,int maxhp, int shield,int maxshield,int st,int maxSt);
	//���� �Է��ϸ� ����� �ش�.
	void ShowBounty(Graphics * gm, int bounty);
	//�� �̳Ѱ��̶� ���� �Ѿ˼�, ���� �Ѿ� ��, �ִ� �Ѿ� ���� �Է��� ����.
	void ShowGun(Graphics * gm, int gunName, int amo, int leftamo,int maxamo);

	
	UI();
	~UI();
};

