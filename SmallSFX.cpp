#include "stdafx.h"
#include "SmallSFX.h"

void SmallSFX::ShowDamage( int x,int y, int damage)
{
	isOn = true;
	this->x = x;
	this->y = y;
	Axel = 8;
	damagetaken = damage;
}

void SmallSFX::Update(Graphics* gm)
{
	if (isOn == true)
	{
		IMAGE->NumRender(gm, g, x, y, damagetaken / 10);
		IMAGE->NumRender(gm, g, x + 16, y, damagetaken % 10 / 1);
		
		//가속도 줄어든다
		Axel -= 0.4f;
		
		//가속도 대로 빼준다
		y -= Axel;

		//가속도가 없어지면 없애준다
		if (Axel < 0)
		{
			isOn = false;
		}
	}
}


SmallSFX::SmallSFX()
{
	isOn = false;
	x = 0;
	y = 0;
	Axel = 0;
	g = IMAGE->findImg("font_number_0");
}


SmallSFX::~SmallSFX()
{
}
