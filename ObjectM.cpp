#include "stdafx.h"
#include "ObjectM.h"
#include "SystemInfo.h"
SINGLETON_S(ObjectM)
//-------------------------------------------
ObjectM * ObjectM::GetInstance()
{
	if (instance)
		return instance;
	return nullptr;
}
//-------------------------------------------
void ObjectM::Init()
{
	for (UINT i = 0; i < Category::END_CATEGORY; ++i)
	{
		objectPool[(Category)i] = vector<Object*>();
	}
}
//-------------------------------------------
void ObjectM::Release()
{
	// 오브젝트 제거 및 해제
	for (UINT i = 0; i < objectPool.size(); ++i)
	{
		for (UINT j = 0; j < objectPool[(Category)i].size(); ++j)
		{
			delete objectPool[(Category)i][j];
			objectPool[(Category)i][j] = nullptr;
			SAFE_DELETE(objectPool[(Category)i][j]);
		}
	}
	// 타일 제거 및 해제
	for (UINT i = 0; i < tilePool.size(); ++i)
	{
		for (UINT j = 0; j < tilePool[i].size(); ++j)
		{
			delete tilePool[i][j];
			tilePool[i][j] = nullptr;
			SAFE_DELETE(tilePool[i][j]);
		}
	}
}
//-------------------------------------------

class Object;
class Pinky;
class Gun;

void GunSwap(Pinky* p, Gun* p2)
{
	GUN tempGun = p->GetGun();
	p->SetBulletID(p2->GetGun());
	p2->SetGun(tempGun);
}



void ObjectM::UpdateObject()
{
	for (UINT i = 0; i < objectPool.size(); ++i)					//맵
	{
		for (UINT j = 0; j < objectPool[(Category)i].size(); ++j)	//벡터
		{
			if (objectPool[(Category)i][j]->IsAlive())				//오브젝트 클래스 포인터
				objectPool[(Category)i][j]->Update();
		}

	}

	//충돌처리(필요 없음)플레이어와 에너미 충돌 -> 에너미 DAMAGE에 따른 플레이어 HP감소

	//RECT rc = { 0,0,0,0 };
	//for (UINT i = 0; i < objectPool[C_ENEMY].size(); ++i)
	//{
	//	// 핑키 충돌박스 & 에너미 충돌박스 충돌 시에
	//	if (IntersectRect(&rc,&objectPool[C_PLAYER][0]->getHitBox(),
	//	&objectPool[C_ENEMY][i]->getHitBox()))
	//	{
	//		//핑키 hp 감소(무적일 경우)
	//		objectPool[C_PLAYER][0]->Dameged(objectPool[C_ENEMY][i]->getDamage(), 
	//			objectPool[C_PLAYER][0]->GetAbsolute());
	//		
	//
	//		//에너미  hp 감소
	//		//objectPool[C_ENEMY][i]->Dameged(objectPool[C_ENEMY][i]->getDamage());
	//
	//	}
	//}




	//플레이어, 아이템 ->
	RECT rc = { 0,0,0,0 };
		for (UINT i = 0; i < objectPool[C_ITEM].size(); ++i)
		{
			
				if (IntersectRect(&rc, &objectPool[C_PLAYER][0]->getHitBox(),
					&objectPool[C_ITEM][i]->getHitBox()))
				{
					Bullet* tempBullet = dynamic_cast<Bullet*>(objectPool[C_BULLET][0]);

					for (int j = 0; j < objectPool[C_BULLET].size(); j++)
					{
						if (objectPool[C_BULLET][j]->getId() == C_PLAYER)
						{
							tempBullet = dynamic_cast<Bullet*>(objectPool[C_BULLET][j]);
							break;
						}
					}

					Bomb* tempBomb = dynamic_cast<Bomb*>(objectPool[C_ITEM][i]);
					//아이템은 픽업 모션을 보여주고 사라지게 만들고
					if (objectPool[C_ITEM][i]->IsSameID(I_BOMB) &&
						INPUT->isOnceDown('E'))
					{
						tempBomb->IsPickUp();

						//플레이어가 가지고 있는 불렛은 충전된다
						tempBullet->SetCharge();
						tempBullet->bombCharge(tempBomb->GetBomb());

					}

					Pinky* tempPinky = dynamic_cast<Pinky*>(objectPool[C_PLAYER][0]);
					HealandShild* tempHealShild = dynamic_cast<HealandShild*>(objectPool[C_ITEM][i]);
					if (objectPool[C_ITEM][i]->IsSameID(I_HEAL_SHILD) &&
						INPUT->isOnceDown('E'))
					{
						//objectPool[C_PLAYER][0]->setHp(objectPool[C_PLAYER][0]->getHp() + 10);
						//플레이어의 HP 또는 SHILD는 회복된다
						tempPinky->SetCharge();
						tempPinky->ItemCharge(tempHealShild->GetItem());
						tempHealShild->isAliveBool();//아이템은 사라지고

					}

					Gun* tempGun = dynamic_cast<Gun*>(objectPool[C_ITEM][i]);
					if (objectPool[C_ITEM][i]->IsSameID(I_GUN) &&
						INPUT->isOnceDown('E'))
					{

						GunSwap(tempPinky, tempGun);
						//tempGun->isAliveBool();

					}


				}

			
			
		}
}
//-------------------------------------------
void ObjectM::RenderObject()
{
	for (UINT i = 0; i < objectPool.size(); ++i)
	{
		for (UINT j = 0; j < objectPool[(Category)i].size(); ++j)
		{
			if (objectPool[(Category)i][j]->IsAlive())
				objectPool[(Category)i][j]->Render();
		}
	}
}

void ObjectM::RenderObject(UI* ui)
{
	for (UINT i = 0; i < objectPool.size(); ++i)
	{
		for (UINT j = 0; j < objectPool[(Category)i].size(); ++j)
		{
			if (objectPool[(Category)i][j]->IsAlive())
				objectPool[(Category)i][j]->Render();
		}
	}
}
//-------------------------------------------
void ObjectM::RenderTile()
{

}
//-------------------------------------------
void ObjectM::CreateObject(Object* p,ObjectID id_)
{
	objectPool[IDtoCategory(id_)].push_back(p);

}
//-------------------------------------------
void ObjectM::CreateTile(Tile* p)
{

}
//-------------------------------------------
Category ObjectM::IDtoCategory(ObjectID ID_)
{
	switch (ID_)
	{
	case ObjectInfo::P_PINKY:
		return ObjectInfo::C_PLAYER;
		break;
	case ObjectInfo::E_DUCK:
		return ObjectInfo::C_ENEMY;
		break;
	case ObjectInfo::E_KAMIKAZE:
		return ObjectInfo::C_ENEMY;
		break;
	case ObjectInfo::B_SINGLE:
		return ObjectInfo::C_BULLET;
		break;
	case ObjectInfo::B_SHOTGUN:
		return ObjectInfo::C_BULLET;
		break;
	case ObjectInfo::B_AUTO:
		return ObjectInfo::C_BULLET;
		break;
	case ObjectInfo::I_GUN:
		return ObjectInfo::C_ITEM;
	case ObjectInfo::I_BOMB:
		return ObjectInfo::C_ITEM;
		break;
	case ObjectInfo::I_HEAL_SHILD:
		return ObjectInfo::C_ITEM;
		break;
	case ObjectInfo::END_OBJECTID:
	default:
		break;
	}
	return END_CATEGORY;
}
//-------------------------------------------
vector<Object*> ObjectM::CategorytoVector(Category C_)
{
	switch (C_)
	{
	case ObjectInfo::C_PLAYER:
		return objectPool[ObjectInfo::C_PLAYER];
		break;
	case ObjectInfo::C_ENEMY:
		return objectPool[ObjectInfo::C_ENEMY];
		break;
	case ObjectInfo::C_BULLET:
		return objectPool[ObjectInfo::C_BULLET];
		break;
	case ObjectInfo::C_ITEM:
		return objectPool[ObjectInfo::C_ITEM];
		break;
	default:
		break;
	}
	return vector<Object*>();
}