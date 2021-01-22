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
		
		//���ӵ� �پ���
		Axel -= 0.4f;
		
		//���ӵ� ��� ���ش�
		y -= Axel;

		//���ӵ��� �������� �����ش�
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
