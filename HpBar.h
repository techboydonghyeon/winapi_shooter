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

	//�׳� hp��(���α׷��� ��?) �׷��ִ� �Լ�
	void DrawHp(Graphics* gm, int x, int y, int hp, int hpMax);

};

