#include "stdafx.h"
#include "UI.h"
#include "SystemInfo.h"


void UI::Init()
{
	//������ hp �κ� ǥ���Ϸ��� ����°�
	hpbar0 = IMAGE->findImg("hpbar_0");
	hpbar1 = IMAGE->findImg("hpbar_1");
	hpbar2 = IMAGE->findImg("hpbar_2");

	shbar0 = IMAGE->findImg("shbar_0");
	shbar1 = IMAGE->findImg("shbar_1");
	shbar2 = IMAGE->findImg("shbar_2");

	//���� ���¹̳� �� ��� �Ⱦ���
	//shieldStamina = IMAGE->findImg("shieldstamina");

	//��Ű ����
	pinkyFace[0] = IMAGE->findImg("pinky_0");
	pinkyFace[1] = IMAGE->findImg("pinky_1");
	pinkyFace[2] = IMAGE->findImg("pinky_2");

	//��Ʈ 3��
	fonts[0] = IMAGE->findImg("font_number_0");
	fonts[1] = IMAGE->findImg("font_number_1");
	fonts[2] = IMAGE->findImg("font_number_2");

	//��� ����
	interval[0] = 16;
	interval[1] = 20;
	interval[2] = 32;

	//���¹̳� ��
	stbar = IMAGE->findImg("staminabar");
	stbar_U = IMAGE->findImg("staminabar3");
	stbars[0] = IMAGE->findImg("staminabar2");
	stbars[1] = IMAGE->findImg("staminabar2");

	starbar = IMAGE->findImg("star_bar");

	guns[0] = IMAGE->findImg("pistol");
	guns[1] = IMAGE->findImg("shotgun");
	guns[2] = IMAGE->findImg("machinegun");

	ammobar = IMAGE->findImg("ammo_bar");
	ammobar2 = IMAGE->findImg("ammo_barB");
}

//���ڸ��� �����ִ� �Լ� ������ ���ڴ� ������ ������ 1 : ���� 2 : �߰� 3 : ŭ
void UI::ShowNumberH(Graphics* gm,int x, int y, int num,int font)
{
	int third = num / 100;
	int second = num % 100 / 10;
	int first = num % 100 % 10 / 1;

	if (num < 0)
	{
		third = 0;
		second = 0;
		first = 0;
	}

	if (!third == 0)
	{
		IMAGE->NumRender(gm, fonts[font], x, y, third);
	}
	if(!second==0||!third==0)
		IMAGE->NumRender(gm, fonts[font], x + interval[font], y, second);
	IMAGE->NumRender(gm, fonts[font], x + interval[font] * 2, y, first);
}

//�ټ� �ڸ��� ���� �����ټ� �ִ� �Լ�
void UI::ShowNumberB(Graphics* gm, int x, int y, int num, int font)
{
	int fifth = num / 10000;
	int fourth = num % 10000 / 1000;
	int third = num % 10000 % 1000 / 100;
	int second = num % 10000 % 1000 % 100 / 10;
	int first = num % 10000 % 1000 % 100 % 10 / 1;

	if (num < 0)
	{
		fifth = 0;
		fourth = 0;
		third = 0;
		second = 0;
		first = 0;
	}

	if (!fifth == 0)
	{
		IMAGE->NumRender(gm, fonts[font], x, y, fifth);
	}
	if (!fifth == 0 || !fourth == 0)
	{
		IMAGE->NumRender(gm, fonts[font], x + interval[font], y, fourth);
	}
	if (!fifth == 0 || !fourth == 0||!third == 0)
	{
		IMAGE->NumRender(gm, fonts[font], x + interval[font] * 2, y, third);
	}
	if (!fifth == 0 || !fourth == 0 || !third == 0 || !second == 0)
	{
		IMAGE->NumRender(gm, fonts[font], x + interval[font] * 3, y, second);
	}

	IMAGE->NumRender(gm, fonts[font], x + interval[font] * 4, y, first);
}

//�μ� ��� �״�� ���� hp, �ִ� hp ���� ����, �ִ� ���带 ��������
void UI::ShowHpBar(Graphics* gm,int hp,int maxhp,int shield,int maxshield,int st,int maxSt)
{
	//��¿�� ���� ������ ���� ������
	static float hp2 = (float)maxhp;
	static float sh2 = (float)maxshield;

	//���� �˻�
	if (hp2 > hp)
	{
		hp2 -= DECREASESPEED;
	}
	if (hp2 < hp)
	{
		hp2 = hp;
	}
	if (sh2 > shield)
	{
		sh2 -= DECREASESPEED;
	}
	if (sh2 < shield)
	{
		sh2 = shield;
	}
	
	//hp ��ο�
	//IMAGE->render(gm, hpbar1->GetGimg(), 130, 55);
	gm->DrawImage(hpbar1->GetGimg(), 130, 55);	//�̹��� Ÿ�� ���� ������� �캽 �ű⼭ �ű�� ����
	IMAGE->BarRender(gm, hpbar2, 125, 50, hp2, maxhp);
	IMAGE->BarRender(gm, hpbar0, 125, 50, hp, maxhp);
	ShowNumberH(gm, 280, 54, hp, 1);

	//���� ��ο�
	//IMAGE->render(gm, shbar1->GetGimg(), 130, 95);
	gm->DrawImage(shbar1->GetGimg(), 130, 95);
	IMAGE->BarRender(gm, shbar2, 125, 90, sh2, maxshield);
	IMAGE->BarRender(gm, shbar0, 125, 90, shield, maxshield);
	ShowNumberH(gm, 280, 96, shield, 0);

	//���¹̳� ��ο�
	gm->DrawImage(stbar_U->GetGimg(), 132, 137);
	IMAGE->BarRender(gm, stbar, 130, 133, st, maxSt);
	if (st > 100)
	{
		gm->DrawImage(stbars[0]->GetGimg(), 130, 133);
	}
	if (st >= 200)
	{
		gm->DrawImage(stbars[1]->GetGimg(), 237, 133);
	}

	//�� ���׸��� �κ�
	if (hp < maxhp / 5)
	{
		//IMAGE->render(gm, pinkyFace[2], 25, 25);
		gm->DrawImage(pinkyFace[2]->GetGimg(), 25, 25);
	}
	else if (hp < maxhp / 2)
	{
		//IMAGE->render(gm, pinkyFace[1], 25, 25);
		gm->DrawImage(pinkyFace[1]->GetGimg(), 25, 25);
	}
	else
		gm->DrawImage(pinkyFace[0]->GetGimg(), 25, 25);

	//IMAGE->render(gm, pinkyFace[0], 25, 25);
	
}

//�� �����ִ� �Լ� �׳� ���� �־�����
void UI::ShowBounty(Graphics* gm, int bounty)
{
	gm->DrawImage(starbar->GetGimg(), _WINSIZEX / 2 - 112, 80);
	ShowNumberB(gm, _WINSIZEX / 2+10, 102, bounty, 1);
}

//�� �����ִ� �Լ� 
void UI::ShowGun(Graphics* gm,int gunName, int amo, int leftamo,int maxamo)
{
	gm->DrawImage(guns[gunName]->GetGimg(), 50, 670);
	gm->DrawImage(ammobar2->GetGimg(), 230, 672);
	IMAGE->BarRender(gm, ammobar, 230, 672, leftamo, maxamo);
	ShowNumberH(gm, 130, 670, amo, 2);
	ShowNumberH(gm, 230, 690, leftamo, 0);
}


UI::UI()
{
}


UI::~UI()
{
}
