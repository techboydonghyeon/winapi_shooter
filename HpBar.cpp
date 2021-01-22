#include "stdafx.h"
#include "HpBar.h"


HpBar::HpBar()
{
	backbar = IMAGE->findImg("objecthpB");
	hpbar = IMAGE->findImg("objecthp");
	whitebar = IMAGE->findImg("objecthpW");

}


HpBar::~HpBar()
{
	
}

void HpBar::DrawHp(Graphics* gm, int x, int y, int hp, int hpMax)
{
	static float hp2 = (float)hpMax;

	gm->DrawImage(backbar->GetGimg(), x + 3, y + 3);
	IMAGE->BarRender(gm, whitebar, x, y, hp2, hpMax);
	IMAGE->BarRender(gm, hpbar, x, y, hp, hpMax);

	if (hp2 < hp)
	{
		hp2 = hp;
	}
	if (hp2 > hp)
	{
		hp2 -= 0.7f;
	}
}
