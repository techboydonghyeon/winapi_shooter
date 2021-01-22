#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::Bullet(ObjectID ID_, ObjectID bulletID_, int x_, int y_)
{
	isOnceCharge = 0;
	//ID = ID_, x = x_, y = y_;
	ID = ID_;
	isAlive = true;
	_bullet.center.x = x_;
	_bullet.center.y = y_;
	_bullet.radius = 10;
	_bullet.angle = 0;
	_bullet.speed = 20;
	_bullet.rc = { (LONG)(_bullet.center.x - _bullet.radius), (LONG)(_bullet.center.y - _bullet.radius),
	(LONG)(_bullet.center.x + _bullet.radius), (LONG)(_bullet.center.y + _bullet.radius) };
	_bullet.fire = false;


	bulletNum_single = 120;				//ÃÑ ºÒ·¿°¹¼ö º¯¼ö
	magazine_single = 25;				//ÅºÃ¢¿¡ µé¾îÀÖ´Â ºÒ·¿°¹¼ö

	bulletNum_shotgun = 25;				//ÃÑ ºÒ·¿°¹¼ö º¯¼ö
	magazine_shotgun = 50;				//ÅºÃ¢¿¡ µé¾îÀÖ´Â ºÒ·¿°¹¼ö

	bulletNum_auto = 100; 				//ÃÑ ºÒ·¿°¹¼ö º¯¼ö
	magazine_auto = 100;

	shotGunCount = 0;



	_vBullet.reserve(20);

	for (int i = 0; i < 20; i++)
	{
		_vBullet.push_back(_bullet);
	}
	//this->bulletFire(ID_, _id, x_, y_);

	OBJECT->CreateObject(this, bulletID_);

	//ºÒ·¿ ÀÌ¹ÌÁö Ã£±â
	bulletImage = IMAGE->findImg("spr_bullet_stronger_0");
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
}

void Bullet::Update()
{

	DATA->setBullet(this);
}

void Bullet::Render()
{
	UINT size = _vBullet.size();

	Gdiplus::Graphics gm(_mdc);

	for (int i = 0; i < size; i++)
	{
		if (_vBullet[i].fire)
		{
			//Rectangle(_mdc, _vBullet[i].rc.left - CAMERA->getCamRc().left, 
			//	_vBullet[i].rc.top - CAMERA->getCamRc().top,
			//	_vBullet[i].rc.right - CAMERA->getCamRc().left,
			//	_vBullet[i].rc.bottom - CAMERA->getCamRc().top);
			CAMERA->CAM_RENDER(&gm, bulletImage, _vBullet[i].center.x, _vBullet[i].center.y);

		}
	}

	char test[200];

	//ÀåÅº¼ö °¨¼Ò Ã¼Å©
	//±âº»¼ÒÃÑ





}

void Bullet::Release()
{
}


void Bullet::ChangeImg()
{
}

void Bullet::bulletAngle(float x, float y)
{

}

ObjectID Bullet::bulletFire(ObjectID bulletID_, float x_, float y_, float angle_)
{
	UINT size = _vBullet.size();
	for (int i = 0; i < size; i++)
	{
		if (_vBullet[i].fire == false)
		{
			_vBullet[i].center.x = x_;
			_vBullet[i].center.y = y_;
		}
	}
	switch (bulletID_)
	{

	case ObjectInfo::B_SINGLE:
		for (int i = 0; i < size; i++)
		{
			if (_vBullet[i].fire) continue;
			else 
			{
				_vBullet[i].fire = true;
				_vBullet[i].angle = angle_;
				magazine_single--;
				return B_SINGLE;
			}
			if (magazine_single < 0)
			{
				magazine_single = 0;
			}
		
		}
		damage = 10;
		break;
	case ObjectInfo::B_SHOTGUN:
		tagBullet* vb[5];
		for (int i = 0; i < size; i++)
		{
			if (_vBullet[i].fire == false)
			{
				if (magazine_shotgun > 0)
				{
					vb[shotGunCount] = &_vBullet[i];
					vb[shotGunCount]->angle = angle_ - 0.4 + shotGunCount * 0.2;
					vb[shotGunCount]->fire = true;
					shotGunCount++;
					magazine_shotgun--;
				}
				if (magazine_shotgun < 0)
				{
					magazine_shotgun = 0;
				}
			}

			if (shotGunCount == 5)
			{
				shotGunCount = 0;
				return B_SHOTGUN;
			}
		}
		damage = 8;
		break;
	case ObjectInfo::B_AUTO:

		for (int i = 0; i < size; i++)
		{
			if (_vBullet[i].fire) continue;
			else if (magazine_auto > 0)
			{
				_vBullet[i].fire = true;
				_vBullet[i].angle = angle_;
				magazine_auto--;
				return B_AUTO;
			}
			else if (magazine_auto <0)
			{
				magazine_auto = 0;
			}
		
			
		}
		damage = 6;
		break;
	default:
		break;
	}
	for (int i = 0; i < size; i++)
	{
		if (_vBullet[i].angle < 0)
		{
			_vBullet[i].angle += 2 * PI;
		}
		if (_vBullet[i].angle > 2 * PI)
		{
			_vBullet[i].angle -= 2 * PI;
		}
	}

}



void Bullet::bulletMove(float x_, float y_)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].fire == false)
		{
			_vBullet[i].center.x = x_;
			_vBullet[i].center.y = y_;
		}
		_vBullet[i].center.x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].center.y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].rc = { (LONG)(_vBullet[i].center.x - _vBullet[i].radius), (LONG)(_vBullet[i].center.y - _vBullet[i].radius),
		   (LONG)(_vBullet[i].center.x + _vBullet[i].radius), (LONG)(_vBullet[i].center.y + _vBullet[i].radius) };
		if (_vBullet[i].center.x < 0 + CAMERA->getCamRc().left || _vBullet[i].center.x > _WINSIZEX + CAMERA->getCamRc().left || _vBullet[i].center.y < 0 + CAMERA->getCamRc().top || _vBullet[i].center.y > _WINSIZEY + CAMERA->getCamRc().top)
		{
			_vBullet[i].fire = false;
		}
		if (OBJECT->IDtoCategory(ID) == C_PLAYER)
		{
			vector<Object*>tempObject1 = OBJECT->CategorytoVector(C_ENEMY);
			vector<Object*>tempObject2 = OBJECT->CategorytoVector(C_STRUCT);
			UINT size1 = tempObject1.size();
			UINT size2 = tempObject2.size();
			for (int k = 0; k < size1; k++)
			{
				if (IntersectRect(&empty, &_vBullet[i].rc, &tempObject1[k]->getHitBox()))
				{
					_vBullet[i].fire = false;
					tempObject1[k]->setHp(tempObject1[k]->getHp() - damage);
				}
			}
			for (int k = 0; k < size2; k++)
			{
				if (IntersectRect(&empty, &_vBullet[i].rc, &tempObject2[k]->getHitBox()))
				{
					_vBullet[i].fire = false;
					tempObject2[k]->setHp(tempObject2[k]->getHp() - damage);
				}
			}
		}
		if (OBJECT->IDtoCategory(ID) == C_ENEMY)
		{
			vector<Object*>tempObject1 = OBJECT->CategorytoVector(C_PLAYER);
			vector<Object*>tempObject2 = OBJECT->CategorytoVector(C_STRUCT);
			UINT size1 = tempObject1.size();
			UINT size2 = tempObject2.size();
			for (int k = 0; k < size1; k++)
			{
				if (IntersectRect(&empty, &_vBullet[i].rc, &tempObject1[k]->getHitBox()))
				{
					_vBullet[i].fire = false;
					tempObject1[k]->setHp(tempObject1[k]->getHp() - damage);
				}
			}
			for (int k = 0; k < size2; k++)
			{
				if (IntersectRect(&empty, &_vBullet[i].rc, &tempObject2[k]->getHitBox()))
				{
					_vBullet[i].fire = false;
					tempObject2[k]->setHp(tempObject2[k]->getHp() - damage);
				}
			}
		}
		//for (int j = 0; j < END_OBJECTID; j++)
		//{
		//   ObjectID id;
		//   id = (ObjectID)j;
		//   //Ä«Å×°í¸®°¡ ´Ù¸£°í Ä«Å×°í¸®°¡ ÃÑ¾ËÀÌ ¾Æ´Ñ°Í
		//   if (OBJECT->IDtoCategory(ID) != OBJECT->IDtoCategory(id) && OBJECT->IDtoCategory(id) != C_BULLET)
		//   {
		//
		//      vector<Object*>tempObject = OBJECT->CategorytoVector(OBJECT->IDtoCategory(id));
		//      UINT size = tempObject.size();
		//      for (int k = 0; k < size; k++)
		//      {
		//         if (IntersectRect(&empty, &_vBullet[i].rc, &tempObject[k]->getHitBox()))
		//         {
		//            _vBullet[i].fire = false;
		//            tempObject[k]->setHp(tempObject[k]->getHp() - damage);
		//         }
		//      }
		//   }
		//}
	}
}

void Bullet::bulletChange(ObjectID bulletID_, float x_, float y_, float angle_)
{
	_vBullet.clear();
	this->bulletFire(bulletID_, x_, y_, angle_);
}

void Bullet::bulletCharge(ObjectID bulletID_)
{

	switch (bulletID_)
	{
	case ObjectInfo::B_SINGLE:
		if (magazine_single == 0)
		{
			magazine_single += 12;
			bulletNum_single -= 12;
		}
		break;
	case ObjectInfo::B_SHOTGUN:
		if (magazine_shotgun == 0)
		{
			magazine_shotgun+=20;
			bulletNum_shotgun-=20;
		}
		break;
	case ObjectInfo::B_AUTO:
		if (magazine_auto == 0)
		{
			magazine_auto +=12;
			bulletNum_auto -=12;
		}
		break;
	
	}

	
}

void Bullet::bombCharge(BOMB bomb_)
{
	if (isOnceCharge == 1)
	{
		switch (bomb_)
		{
		case LIHGT_BOMB:
			bulletNum_single +=12;
			break;
		case MIDIUM_BOMB:
			bulletNum_shotgun += 20;
			break;
		case HEAVY_BOMB:
			bulletNum_auto +=12;
			break;
		}
	}
}

void Bullet::SetCharge()
{
	isOnceCharge++;

}

int Bullet::GetBulletNum()
{
	switch (gun)
	{
	case PISTOL:
		bulletID = B_SINGLE;
		return bulletNum_single;
		
		break;
	case SHOTGUN:
		bulletID = B_SHOTGUN;
		return bulletNum_shotgun;
		
		break;
	case MACHINEGUN:
		bulletID = B_AUTO;
		return bulletNum_auto;
		
		break;

	}

}

int Bullet::GetMagazineNum()
{
	switch (gun)
	{
	case PISTOL:
		return magazine_single;
		break;
	case SHOTGUN:
		return magazine_shotgun;
		break;
	case MACHINEGUN:
		return magazine_auto;
		break;

	}
}
