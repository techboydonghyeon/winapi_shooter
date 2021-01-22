#pragma once
#include"GpImage.h"
class HpBar
{
private:
	GdiImg* backbar;
	GdiImg* hpbar;
	GdiImg* whitebar;
public:
	HpBar();
	~HpBar();

	//그냥 hp바(프로그레스 바?) 그려주는 함수
	void DrawHp(Graphics* gm, int x, int y, int hp, int hpMax);

};

