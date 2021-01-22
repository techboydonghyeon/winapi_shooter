#pragma once

enum BOMB			//아이템 BOMB
{
	LIHGT_BOMB,
	MIDIUM_BOMB,
	HEAVY_BOMB
};

enum HEAL_SHILID			//아이템 HEAL ANND SHILD
{
	HEAL,
	SHILD,
};

enum GUN					//아이템 GUN
{
	PISTOL,
	SHOTGUN,
	MACHINEGUN
};





class Object
{


protected:
	ObjectID ID; // 객체 정보
	float x;      // 위치 좌표 x
	float y;      // 위치 좌표 y
	float angle;	// 각도
	RECT imageRc;// 이미지 rect
	RECT hitBox; // 충돌 박스
	bool isAlive;// 생존 플래그
	
	int damage;
	int hp;
	int maxHp;
	int absolute;		//핑키클래스 업데이트에서 계속 --되는 변수(핑키무적상태만들어줄때씀)
	int shild;
	int maxShild;
	int st;				//스테미너
	int maxSt;
	int bounty;			//돈




public:
	Object();
	virtual ~Object() {}

	RECT getHitBox() { return hitBox; }
	POINTFLOAT getCenter() { return { x, y }; }

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	virtual bool IsAlive()const { return isAlive; }
	virtual bool IsSameID(ObjectID ID_) const { return ID == ID_ ? true : false; }
	

	int getDamage() { return damage; }
	int getHp() { return hp; }
	void setHp(int hp_) { hp = hp_; }
	int getShild() { return shild; }
	void setShild(int shild_) { shild = shild_; }
	int getSt() { return st; }
	void setSt(int st_) { st = st_; }

	ObjectID getId() { return ID; }
	void setIsAlive(bool isAlive_) { isAlive = isAlive_; }
	void Dameged(int amount_);
	void Dameged(int amount_, int absolute_); //무적상태
	int GetAbsolute() { return absolute; }
	int GetBounty() { return bounty; }
	

	

};

