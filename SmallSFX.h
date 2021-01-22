#pragma once
class SmallSFX
{
private:
	GdiImg* g;

	int x;	//x좌표
	int y;	//y좌표

	bool isOn;//켜져있냐
	int damagetaken;
	float mTime;//만들어진 시간
	float Axel;
public:
	void ShowDamage( int x,int y,int damage);
	void Update(Graphics* gm);
	bool getison() { return isOn; }
	SmallSFX();
	~SmallSFX();
};

