#pragma once
#include "Player.h"
#include "Bullet.h"


enum STATE
{
	IDLE_R,
	IDLE_L,
	WALK_R,
	WALK_L,
	SPRINT_R,
	SPRINT_L,			//달리기
	DASH_R,
	DASH_L,
	MELEE_R,			//근접공격
	MELEE_L,
	TELEPORTIN_R,
	TELEPORTIN_L,
	TELEPORTOUT_R,
	TELEPORTOUT_L,
	HOLO_R,
	HOLO_L,
	HIT_R,
	HIT_L,
	DEATH_R,
	DEATH_L

};


class Pinky : public Player
{
private:

	Bullet* _bullet;
	ObjectID bulletID;
	int count;
	GdiImg* gunImage;
	int a;
	
	
	GdiImg* pinkyImage;
	char debugtext[100];
	RECT Mrc;
	STATE state;

	int isOnceCharge;

	//불렛들


	//현재 탄창에 들어있는 총알
	int lightbullet;
	int mediumbullet;
	int heavybullet;

	//현재 소지 총알 개수
	int maxLightBullet;
	int maxMediumBullet;
	int maxHeavyBullet;





public:
	Pinky(ObjectID ID_, int x_, int y_);
	virtual ~Pinky();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	float getAngle(float startX, float startY, float endX, float endY);


	//=======pinky===========
	void ImageFind(STATE state_);
	void keyInput();
	void Move();



	//=======gun===========
	void ImageFind(ObjectID ID_);
	virtual bool IsAlive()const { return isAlive; }
	virtual bool IsSameID(ObjectID ID_) const { return ID == ID_ ? true : false; }
	void GunCharge(GUN gun_);
	GUN GetGun();


	//=======bullet===========
	ObjectID GetBulletID() { return bulletID; }
	void SetBulletID(ObjectID bulletID_) { bulletID = bulletID_; }
	int GetbulletNum();


	//=====hp, shild =============
	void ItemCharge(HEAL_SHILID hs_);
	void SetCharge();

};


