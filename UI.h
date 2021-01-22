#pragma once
#include"GpImage.h"

#define NUMWIDTH 20
#define DECREASESPEED 0.7f

class UI
{
private:
	//HP 바에 관련된 변수들
	GdiImg* pinkyFace[3];//핑키 얼굴 이미지 3개
	GdiImg* shieldStamina;//쉴드, 스태미나
	GdiImg* fonts[3];	//폰트 쓰려면 여기 넣고 쓰자

	int interval[3];	//각 폰트 마다 거리

	GdiImg* hpbar0;		//hp 바
	GdiImg* hpbar1;
	GdiImg* hpbar2;

	GdiImg* shbar0;		//쉴드 바
	GdiImg* shbar1;
	GdiImg* shbar2;

	GdiImg* stbar;		//스태미너 바
	GdiImg* stbars[2];	//스태미너 바1
	GdiImg* stbar_U;

	//돈 표시
	GdiImg* starbar;	//돈 보이는 바

	//총 표시
	GdiImg* guns[3];		//총 가지고 있기
	GdiImg* ammobar;		//총알 바
	GdiImg* ammobar2;		//총알 언더 바



public:
	void Init();

	//3자리수 숫자 출력하는 함수 폰트는 0,1,2 가 있다. 작은 크기 순서다
	void ShowNumberH(Graphics* gm,int x, int y, int num,int font);
	//5자리수 숫자 출력하는 함수 포느는 위와 같다
	void ShowNumberB(Graphics * gm, int x, int y, int num, int font);
	//hp 바,쉴드 바, 스태머너 바 를 보여주는 함수 그냥 보이는 대로 입력하면 된다.
	void ShowHpBar(Graphics * gm, int hp,int maxhp, int shield,int maxshield,int st,int maxSt);
	//돈을 입력하면 출력해 준다.
	void ShowBounty(Graphics * gm, int bounty);
	//총 이넘값이랑 현재 총알수, 남은 총알 수, 최대 총알 수를 입력해 주자.
	void ShowGun(Graphics * gm, int gunName, int amo, int leftamo,int maxamo);

	
	UI();
	~UI();
};

