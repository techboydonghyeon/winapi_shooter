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
	
	// �ʱ�ȭ �� ����
	void Init();
	void Release();

	// ������Ʈ �� Ÿ�� ������Ʈ & ������
	void UpdateObject();
	void RenderObject();
	void RenderObject(UI * ui);
	void RenderTile();

	// ������Ʈ �� Ÿ�� ����
	void CreateObject(Object*, ObjectID);
	void CreateTile(Tile*);

	// ID ���� ī�װ��� ����
	Category IDtoCategory(ObjectID);

	vector<Object*> CategorytoVector(Category);

	TilePool GetTilePool() const { return tilePool; }
	ObjectPool GetObjectPool() const { return objectPool; }

};

