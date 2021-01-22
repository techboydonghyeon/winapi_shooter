#include "stdafx.h"
#include "UI.h"
#include "SystemInfo.h"


void UI::Init()
{
	//여부터 hp 부분 표시하려고 만드는거
	hpbar0 = IMAGE->findImg("hpbar_0");
	hpbar1 = IMAGE->findImg("hpbar_1");
	hpbar2 = IMAGE->findImg("hpbar_2");

	shbar0 = IMAGE->findImg("shbar_0");
	shbar1 = IMAGE->findImg("shbar_1");
	shbar2 = IMAGE->findImg("shbar_2");

	//쉴드 스태미나 바 사실 안쓴다
	//shieldStamina = IMAGE->findImg("shieldstamina");

	//핑키 을굴
	pinkyFace[0] = IMAGE->findImg("pinky_0");
	pinkyFace[1] = IMAGE->findImg("pinky_1");
	pinkyFace[2] = IMAGE->findImg("pinky_2");

	//폰트 3개
	fonts[0] = IMAGE->findImg("font_number_0");
	fonts[1] = IMAGE->findImg("font_number_1");
	fonts[2] = IMAGE->findImg("font_number_2");

	//띄는 범위
	interval[0] = 16;
	interval[1] = 20;
	interval[2] = 32;

	//스태미너 바
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

//세자리수 보여주는 함수 마지막 인자는 숫자의 종류다 1 : 작음 2 : 중간 3 : 큼
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

//다섯 자리수 까지 보여줄수 있는 함수
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

//인수 목록 그대로 현재 hp, 최대 hp 현재 쉴드, 최대 쉴드를 적어주자
void UI::ShowHpBar(Graphics* gm,int hp,int maxhp,int shield,int maxshield,int st,int maxSt)
{
	//어쩔수 없이 선택한 정적 변수들
	static float hp2 = (float)maxhp;
	static float sh2 = (float)maxshield;

	//조건 검사
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
	
	//hp 드로우
	//IMAGE->render(gm, hpbar1->GetGimg(), 130, 55);
	gm->DrawImage(hpbar1->GetGimg(), 130, 55);	//이미지 타고 들어가면 느릴까봐 헤봄 거기서 거긴거 같다
	IMAGE->BarRender(gm, hpbar2, 125, 50, hp2, maxhp);
	IMAGE->BarRender(gm, hpbar0, 125, 50, hp, maxhp);
	ShowNumberH(gm, 280, 54, hp, 1);

	//쉴드 드로우
	//IMAGE->render(gm, shbar1->GetGimg(), 130, 95);
	gm->DrawImage(shbar1->GetGimg(), 130, 95);
	IMAGE->BarRender(gm, shbar2, 125, 90, sh2, maxshield);
	IMAGE->BarRender(gm, shbar0, 125, 90, shield, maxshield);
	ShowNumberH(gm, 280, 96, shield, 0);

	//스태미나 드로우
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

	//얼굴 찡그리는 부분
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

//돈 보여주는 함수 그냥 값을 넣어주자
void UI::ShowBounty(Graphics* gm, int bounty)
{
	gm->DrawImage(starbar->GetGimg(), _WINSIZEX / 2 - 112, 80);
	ShowNumberB(gm, _WINSIZEX / 2+10, 102, bounty, 1);
}

//총 보여주는 함수 
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
