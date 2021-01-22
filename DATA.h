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

	//임포트할 이미지의 정보가 저장 되어있는 텍스트 파일의 이름을 적어주자
	//그럼 파일의 양식대로 임포트된다 필요하다면 경로까지 적어주자
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

