#pragma once
#include"Object.h"

class Data
{
private:
	static Data* instance;

	Object* playa;
	Object* bullet;

	SINGLETON_H(Data)
public:

	//����Ʈ�� �̹����� ������ ���� �Ǿ��ִ� �ؽ�Ʈ ������ �̸��� ��������
	//�׷� ������ ��Ĵ�� ����Ʈ�ȴ� �ʿ��ϴٸ� ��α��� ��������
	void importFoler(const char* filename);
	void importFolerObject(const char* filename);
	void importFolerTile(const char* filename);

	void Init();

	static Data* GetInstance() {
		if (instance)
			return instance;
		return nullptr;
	}


	void setPlaya(Object* obj)
	{
		playa = obj;
	}
	void setBullet(Object* obj)
	{
		bullet = obj;
	}

	Object* getPlaya() { return playa; }

	Object* getBullet() { return bullet; }

	void seeifcan() {}

};

