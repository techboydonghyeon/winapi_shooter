#pragma once
#include"UI.h"

class ObjectM
{
private:
	static ObjectM* instance;
	SINGLETON_H(ObjectM)
private:
	ObjectPool objectPool;
	ObjectPoolIter objectIter;

	TilePool tilePool;
	TilePoolIter tilePoolIter;
	ObjectID ID;

public:
	static ObjectM* GetInstance();
	
	// 초기화 및 해제
	void Init();
	void Release();

	// 오브젝트 및 타일 업데이트 & 렌더링
	void UpdateObject();
	void RenderObject();
	void RenderObject(UI * ui);
	void RenderTile();

	// 오브젝트 및 타일 생성
	void CreateObject(Object*, ObjectID);
	void CreateTile(Tile*);

	// ID 값을 카테고리로 변경
	Category IDtoCategory(ObjectID);

	vector<Object*> CategorytoVector(Category);

	TilePool GetTilePool() const { return tilePool; }
	ObjectPool GetObjectPool() const { return objectPool; }

};

