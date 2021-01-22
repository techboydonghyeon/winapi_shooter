#include "stdafx.h"
#include "Pinky.h"
#include "SystemInfo.h"
#include "UI.h"

Pinky::Pinky(ObjectID ID_, int x_, int y_)
{
	//�Ѿ� ���� �ʱ�ȭ
	lightbullet = 30;
	mediumbullet = 30;
	heavybullet = 50;


	isOnceCharge = 0;
	count = 0;
	bounty = 50000;
	absolute = 0;
	hp = 100;
	shild = 100;
	st = 100;
	damage = 10;

	bulletID = B_SINGLE;
	_bullet = new Bullet(ID_, bulletID, x_ + 40, y_ + 40);
	count = 0;
	a = 0;


	ID = ID_, x = x_, y = y_;
	isAlive = true;
	speed = 4;
	angle = 0;
	isRight = true;
	state = IDLE_R;


	//���콺 Ȯ�ο� ��Ʈ
	Mrc = { _mouse.x - 5, _mouse.y - 5, _mouse.x + 5, _mouse.y + 5 };


	//�÷��̾� Ȯ�ο� ��Ʈ
	imageRc = { (LONG)x, (LONG)y, 100, 100 };

	hitBox = imageRc;


	OBJECT->CreateObject(this, P_PINKY);
	DATA->setPlaya(this);

}

Pinky::~Pinky()
{

}

void Pinky::Init()
{

}

void Pinky::Update()
{
	bounty--;
	count++;

	//��Ȳ�� �´� ��Ű �̹��� ã��
	this->ImageFind(state);

	//��Ű�� �ٶ󺸰� �ִ� ����
	if (x < _mouse.x + CAMERA->getCamRc().left) isRight = true;
	else if (x > _mouse.x + CAMERA->getCamRc().left) isRight = false;

	//��Ű�� �⺻ IDLE �̹��� �ε�
	if (isRight) state = IDLE_R;
	else if (!isRight) state = IDLE_L;

	//ī�޶� ��ġ ����
	CAMERA->SettingCamera(x + 40, y + 40);			

	//��Ű->���콺 ����(�ޱ�) ������Ʈ
	angle = getAngle(x, y, _mouse.x + CAMERA->getCamRc().left,
		_mouse.y + CAMERA->getCamRc().top);

//==========�ҷ�==============
	//Gun �̹��� ã��
	this->ImageFind(bulletID);

	//KeyInput�� ���� ��Ű �̵��� �̹��� �ε�
	this->keyInput();

	//�ҷ��̵�
	_bullet->bulletMove(x + 40, y + 40);


	if (INPUT->isOnceDown('1'))
	{
		bulletID = B_SINGLE;
	}
	if (INPUT->isOnceDown('2'))
	{
		bulletID = B_SHOTGUN;
	}
	if (INPUT->isOnceDown('3'))
	{
		bulletID = B_AUTO;
	}


	//��ġ ��ǥ x,y ���� �޾� ��Ʈ ������Ʈ
	imageRc = { (LONG)x, (LONG)y,
		(LONG)(x + pinkyImage->GetGdiInfo()->imgWidth),
		(LONG)(y + pinkyImage->GetGdiInfo()->imgHeight) };
	hitBox = imageRc;
	absolute--;

}
void Pinky::Render()
{
	Gdiplus::Graphics gm(_mdc);	//�׸��� �ʿ��� ��


	//���콺�� �׽�Ʈ
	sprintf(debugtext, "%d, %d", _mouse.x, _mouse.y);
	TextOut(_mdc, 0, 0, debugtext, strlen(debugtext));


	//���콺 ��Ʈ ����
	Rectangle(_mdc, _mouse.x - 5, 
		_mouse.y - 5, 
		_mouse.x + 5, 
		_mouse.y + 5);


	//��Ű ���� ��Ʈ ����
	Rectangle(_mdc, (LONG)x - CAMERA->getCamRc().left,
		(LONG)y - CAMERA->getCamRc().top,
		(LONG)(x + pinkyImage->GetGdiInfo()->imgWidth - CAMERA->getCamRc().left),
		(LONG)(y + pinkyImage->GetGdiInfo()->imgHeight - CAMERA->getCamRc().top));


	//��Ű �̹��� ����
	CAMERA->CAM_FRAMERENDER(&gm, pinkyImage, x, y, 5);

	//�� �̹��� ����(ȸ������)
	//IMAGE->render(gunImage, x, y, angle);
	IMAGE->render(gunImage, x + gunImage->GetGdiInfo()->imgWidth - CAMERA->getCamRc().left,
		y + gunImage->GetGdiInfo()->imgHeight+45 - CAMERA->getCamRc().top,
		angle*(180/PI));


	//��Ű hp���� Ȯ��
	sprintf(debugtext, "��Ű hp : %d ,%d ,%d ,%d", hp, lightbullet, mediumbullet, heavybullet);
	TextOut(_mdc, 20, 400, debugtext, strlen(debugtext));

	//UI ����

	//ui->ShowBounty(&gm, DATA->getPlaya()->GetBounty());
	//ui->ShowGun(&gm, dynamic_cast<Pinky*>(DATA->getPlaya())->GetGun(), 250, 50, 300);




}

void Pinky::Release()
{
} 

float Pinky::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	float distance = sqrtf(x * x + y * y);
	float angle = acosf(x / distance);
	if (endY > startY)
	{
		angle = 2 * PI - angle;
		if (angle > 2 * PI) angle -= 2 * PI;
	}
	return angle;
}

void Pinky::ImageFind(STATE state_)
{
	state = state_;

	switch (state)
	{
	case IDLE_R:
		pinkyImage = IMAGE->findImg("pinky_idle_right");
		break;
	case IDLE_L:
		pinkyImage = IMAGE->findImg("pinky_idle_left");
		break;
	case WALK_R:
		pinkyImage = IMAGE->findImg("pinky_walk_right");
		break;
	case WALK_L:
		pinkyImage = IMAGE->findImg("pinky_walk_left");
		break;
	case SPRINT_R:
		pinkyImage = IMAGE->findImg("pinky_sprint_right");
		break;
	case SPRINT_L:
		pinkyImage = IMAGE->findImg("pinky_sprint_left");
		break;
	case DASH_R:
		pinkyImage = IMAGE->findImg("pinky_dash_right");
		break;
	case DASH_L:
		pinkyImage = IMAGE->findImg("pinky_dash_left");
		break;
	case MELEE_R:
		pinkyImage = IMAGE->findImg("pinky_melee_right");
		break;
	case MELEE_L:
		pinkyImage = IMAGE->findImg("pinky_melee_left");
		break;
	case TELEPORTIN_R:
		pinkyImage = IMAGE->findImg("pinky_teleport_in_right");
		break;
	case TELEPORTIN_L:
		pinkyImage = IMAGE->findImg("pinky_teleport_in_left");
		break;
	case TELEPORTOUT_R:
		pinkyImage = IMAGE->findImg("pinky_teleport_out_right");
		break;
	case TELEPORTOUT_L:
		pinkyImage = IMAGE->findImg("pinky_teleport_out_left");
		break;
	case HOLO_R:
		pinkyImage = IMAGE->findImg("pinky_holo_right");
		break;
	case HOLO_L:
		pinkyImage = IMAGE->findImg("pinky_holo_left");
		break;
	case HIT_R:
		pinkyImage = IMAGE->findImg("pinky_hit_right");
		break;
	case HIT_L:
		pinkyImage = IMAGE->findImg("pinky_hit_left");
		break;
	case DEATH_R:
		pinkyImage = IMAGE->findImg("pinky_death_right");
		break;
	case DEATH_L:
		pinkyImage = IMAGE->findImg("pinky_death_left");
		break;
	}

}

void Pinky::keyInput()
{

	//�÷��̾� �̵�
	//�⺻ dash-> ���콺 ���⿡�� �ݴ� �������� �����̵�
	if (!INPUT->isStayDown('W') &&
		!INPUT->isStayDown('S') &&
		!INPUT->isStayDown('A') &&
		!INPUT->isStayDown('D')) //�̵������� �ƴҶ�
	{
		if (INPUT->isStayDown(VK_SHIFT))
		{
			//�̵�����
			angle = getAngle(_mouse.x+ CAMERA->getCamRc().left,
				_mouse.y + CAMERA->getCamRc().top, x, y);

			//�̵�
			x += cos(angle)*speed * 2;
			y -= sin(angle)* speed * 2;

			//�̹��� �ε�
			if (isRight) state = DASH_L;
			else if (!isRight) state = DASH_R;

			//���׹̳� ����
			st -= 1;

		}

	}


	//��
	if (INPUT->isStayDown('W'))
	{
		
		if (INPUT->isStayDown(VK_SHIFT))
		{
			//�̵�
			y -= speed * 2;

			//�̹��� �ε�
			if (isRight) state = SPRINT_R;
			else if (!isRight) state = SPRINT_L;
			//���׹̳� ����
			st -= 1;

		}

		else
		{
			//�̵�
			y -= speed;

			//�̹��� �ε�
			if (isRight) state = WALK_R;
			else if (!isRight) state = WALK_L;
		}
	}

	//�Ʒ�
	if (INPUT->isStayDown('S'))
	{
		if (INPUT->isStayDown(VK_SHIFT))
		{
			//�̵�
			y += speed * 2;

			//�̹��� �ε�
			if (isRight) state = SPRINT_R;
			else if (!isRight) state = SPRINT_L;

			//���׹̳� ����
			st -= 1;
		}
		else
		{
			//�̵�
			y += speed;

			//�̹��� �ε�
			if (isRight) state = WALK_R;
			else if (!isRight) state = WALK_L;

		}

	}

	//��
	if (INPUT->isStayDown('A'))
	{

		if (INPUT->isStayDown(VK_SHIFT))
		{
			//�̵�
			x -= speed * 2;

			//�̹��� �ε�
			if (isRight) state = SPRINT_R;
			else if (!isRight) state = SPRINT_L;

			//���׹̳� ����
			st -= 1;
		}
		else
		{

			//�̵�
			x -= speed;

			//�̹��� �ε�
			if (isRight) state = WALK_R;
			else if (!isRight) state = WALK_L;
		}

	}

	//��
	if (INPUT->isStayDown('D'))
	{

		if (INPUT->isStayDown(VK_SHIFT))
		{
			//�̵�
			x += speed * 2;
			//�̹��� �ε�
			if (isRight) state = SPRINT_R;
			else if (!isRight) state = SPRINT_L;

			//���׹̳� ����
			st -= 1;
		}
		else
		{
			//�̵�
			x += speed;
			//�̹��� �ε�
			if (isRight) state = WALK_R;
			else if (!isRight) state = WALK_L;
		}

	}

	//angle = getAngle(x, y, _mouse.x + CAMERA->getCamRc().left,
	//	_mouse.y + CAMERA->getCamRc().top);


	//melee�� midleButton������ ��  
	//if (INPUT->isStayDown(VK_MBUTTON))
	//{
	//	//�̵�����(��Ű->���콺 ����)
	//	angle = getAngle(x, y, _mouse.x + CAMERA->getCamRc().left,
	//		_mouse.y + CAMERA->getCamRc().top);
	//
	//	//�̵�
	//	x += cos(angle)*speed;
	//	y -= sin(angle)* speed;
	//
	//	//�̹��� �ε�
	//	if (isRight) state = MELEE_R;
	//	else if (!isRight) state = MELEE_L;
	//}
	
	if (INPUT->isOnceDown(VK_LBUTTON))
	{

		//�̹��� �ε�
		if (isRight) state = MELEE_R;
		else if (!isRight) state = MELEE_L;
	
		
		//�ҷ�����
		
		if (!(this->bulletID == B_SINGLE && lightbullet <= 0))
		{

			switch (_bullet->bulletFire(bulletID, x + 40, y + 40, angle))
			{
			case B_SINGLE:
				lightbullet--;
				break;
			case B_SHOTGUN:
				mediumbullet--;
				break;
			default:
				break;
			}
		}
		//_bullet->bulletFire(bulletID, x + 40, y + 40, angle);


	}
	if (INPUT->isStayDown(VK_LBUTTON) && bulletID == B_AUTO)
	{
		//�̹��� �ε�
		if (isRight) state = MELEE_R;
		else if (!isRight) state = MELEE_L;

		count++;
		if (count % 15 == 0)
		{
			_bullet->bulletFire(bulletID, x + 40, y + 40, angle);

			heavybullet--;
		}

	}


	//�ҷ� ������
	if (INPUT->isOnceDown('R'))
	{
		_bullet->bulletCharge(bulletID);
	}

	//�ҷ� �ڵ�����
	if (count % 800 == 0)
	{
		_bullet->bulletCharge(bulletID);
	}

	


}

void Pinky::Move()
{
}

void Pinky::ImageFind(ObjectID ID_)
{
	bulletID = ID_;

	if (bulletID == B_SINGLE)
	{
		gunImage = IMAGE->findImg("pistol_0");
	}
	else if (bulletID == B_SHOTGUN)
	{
		gunImage = IMAGE->findImg("shotgun_0");
	}
	else if (bulletID == B_AUTO)
	{
		gunImage = IMAGE->findImg("machinegun_0");
	}
}

void Pinky::GunCharge(GUN gun_)
{
	
	if (isOnceCharge == 1)
	{
		switch (gun_)
		{
		case PISTOL:
			bulletID = B_SINGLE;
			break;
		case SHOTGUN:
			bulletID = B_SHOTGUN;
			break;
		case MACHINEGUN:
			bulletID = B_AUTO;
		}

	}

}

GUN Pinky::GetGun()
{
	switch (bulletID)
	{
	case B_SINGLE:
		return PISTOL;
		break;
	case B_SHOTGUN:
		return SHOTGUN;
		break; 
	case B_AUTO:
		return MACHINEGUN;
		break;
		
	}
}

void Pinky::ItemCharge(HEAL_SHILID hs_)
{
	if (isOnceCharge == 1)
	{
		switch (hs_)
		{
		case HEAL:
			hp += 30;
			break;
		case SHILD:
			shild += 30;
			break;
		}
	}
}

void Pinky::SetCharge()
{
	isOnceCharge++;
}


