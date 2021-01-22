#pragma once
#include "Object.h"

struct tagBullet
{
	POINTFLOAT center;
	RECT rc;
	float angle;
	float speed;
	float radius;
	bool fire;
};


class Bullet : public Object
{
private:
	int shotGunCount;
	int bulletNum_single;		//ÃÑ ºÒ·¿°¹¼ö º¯¼ö
	int magazine_single;		//ÅºÃ¢¿¡ µé¾îÀÖ´Â ºÒ·¿°¹¼ö
	int bulletNum_shotgun;		//ÃÑ ºÒ·¿°¹¼ö º¯¼ö
	int magazine_shotgun;
	int bulletNum_auto;		//ÃÑ ºÒ·¿°¹¼ö º¯¼ö
	int magazine_auto;

	int isOnceCharge;

	ObjectID bulletID;
	GUN gun;


	GdiImg* bulletImage;
	vector<tagBullet> _vBullet;
	tagBullet _bullet;
	bool _fire;
	RECT empty;
public:
	Bullet();
	Bullet(ObjectID ID_, ObjectID bulletID_, int x_, int y_);
	~Bullet();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();


	//ÀÌ¹ÌÁö ¹Ù²ãÁÙ¶§ ÇÊ¿äÇÑ ÇÔ¼ö
	virtual void ChangeImg();

	void bulletAngle(float x, float y);
	ObjectID bulletFire2(ObjectID bulletID_, float x_, float y_, float angle_);
	ObjectID bulletFire(ObjectID, float, float, float);
	void bulletMove(float, float);
	void bulletChange(ObjectID, float, float, float);
	void bulletCharge(ObjectID);
	void bombCharge(BOMB);
	void SetCharge();


	int GetBulletNumSingle() { return bulletNum_single; }
	void SetBulletNumSingle(int bulletNum_single_) { bulletNum_single = bulletNum_single_; }
	int GetMagazineSingle() { return magazine_single; }
	void SetMagazineSingle(int magazine_single_) { magazine_single = magazine_single_; }
	int GetBulletNumShotGun() { return bulletNum_shotgun; }
	int GetMagazineShotGun() { return magazine_shotgun; }
	int GetBulletNumAuto() { return bulletNum_auto; }
	int GetMagazineAuto() { return magazine_auto; }
	int GetBulletNum();
	int GetMagazineNum();




	virtual bool IsAlive()const { return isAlive; }
	virtual bool IsSameID(ObjectID ID_) const { return ID == ID_ ? true : false; }
};



