#pragma once
#include "Enemy.h"
class Kamikaze :
	public Enemy
{
private:
	GdiImg* sprint;				//이미지 찾기 변수
	GdiImg* sprint1;			//이미지 찾기 변수
	//카미카제 이미지 enum문
	enum KAMIIMAGE
	{
		IDLE,					//가만히 있을 때
		WALK,					//걷기
		DASH,					//대쉬
		ATTACK,					//공격
		PRECISION,				//치명타로 사망
		DEATH					//죽음
	};
	KAMIIMAGE kamiImage;
private:
	int dashCount;				//대쉬에 텀 두기
	int frameCount;			//스피드만큼 몇번 이동할지
	bool dash;					//대쉬하는가?

	char str[256];				//그냥 좌표 확인용 변수
	char str1[256];				//그냥 좌표 확인용 변수

public:
	Kamikaze();
	Kamikaze(ObjectID ID_, int x_, int y_);
	virtual ~Kamikaze();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void InRange();

	//이미지 바꿔줄때 필요한 함수
	virtual void ChangeImg();

	virtual bool IsAlive()const { return isAlive; }
	virtual bool IsSameID(ObjectID ID_) const { return ID == ID_ ? true : false; }

};

