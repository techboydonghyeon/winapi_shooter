#pragma once
class SmallSFX
{
private:
	GdiImg* g;

	int x;	//x��ǥ
	int y;	//y��ǥ

	bool isOn;//�����ֳ�
	int damagetaken;
	float mTime;//������� �ð�
	float Axel;
public:
	void ShowDamage( int x,int y,int damage);
	void Update(Graphics* gm);
	bool getison() { return isOn; }
	SmallSFX();
	~SmallSFX();
};

