#pragma once

enum BOMB			//������ BOMB
{
	LIHGT_BOMB,
	MIDIUM_BOMB,
	HEAVY_BOMB
};

enum HEAL_SHILID			//������ HEAL ANND SHILD
{
	HEAL,
	SHILD,
};

enum GUN					//������ GUN
{
	PISTOL,
	SHOTGUN,
	MACHINEGUN
};





class Object
{


protected:
	ObjectID ID; // ��ü ����
	float x;      // ��ġ ��ǥ x
	float y;      // ��ġ ��ǥ y
	float angle;	// ����
	RECT imageRc;// �̹��� rect
	RECT hitBox; // �浹 �ڽ�
	bool isAlive;// ���� �÷���
	
	int damage;
	int hp;
	int maxHp;
	int absolute;		//��ŰŬ���� ������Ʈ���� ��� --�Ǵ� ����(��Ű�������¸�����ٶ���)
	int shild;
	int maxShild;
	int st;				//���׹̳�
	int maxSt;
	int bounty;			//��




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
	void Dameged(int amount_, int absolute_); //��������
	int GetAbsolute() { return absolute; }
	int GetBounty() { return bounty; }
	

	

};

