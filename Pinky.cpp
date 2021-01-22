#include "stdafx.h"
#include "Pinky.h"
#include "SystemInfo.h"
#include "UI.h"

Pinky::Pinky(ObjectID ID_, int x_, int y_)
{
	//총알 관련 초기화
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


	//마우스 확인용 렉트
	Mrc = { _mouse.x - 5, _mouse.y - 5, _mouse.x + 5, _mouse.y + 5 };


	//플레이어 확인용 렉트
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

	//상황에 맞는 핑키 이미지 찾기
	this->ImageFind(state);

	//핑키가 바라보고 있는 방향
	if (x < _mouse.x + CAMERA->getCamRc().left) isRight = true;
	else if (x > _mouse.x + CAMERA->getCamRc().left) isRight = false;

	//핑키의 기본 IDLE 이미지 로딩
	if (isRight) state = IDLE_R;
	else if (!isRight) state = IDLE_L;

	//카메라 위치 세팅
	CAMERA->SettingCamera(x + 40, y + 40);			

	//핑키->마우스 방향(앵글) 업데이트
	angle = getAngle(x, y, _mouse.x + CAMERA->getCamRc().left,
		_mouse.y + CAMERA->getCamRc().top);

//==========불렛==============
	//Gun 이미지 찾기
	this->ImageFind(bulletID);

	//KeyInput에 따른 핑키 이동과 이미지 로딩
	this->keyInput();

	//불렛이동
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


	//위치 좌표 x,y 값을 받아 렉트 업데이트
	imageRc = { (LONG)x, (LONG)y,
		(LONG)(x + pinkyImage->GetGdiInfo()->imgWidth),
		(LONG)(y + pinkyImage->GetGdiInfo()->imgHeight) };
	hitBox = imageRc;
	absolute--;

}
void Pinky::Render()
{
	Gdiplus::Graphics gm(_mdc);	//그릴때 필요한 거


	//마우스값 테스트
	sprintf(debugtext, "%d, %d", _mouse.x, _mouse.y);
	TextOut(_mdc, 0, 0, debugtext, strlen(debugtext));


	//마우스 렉트 띄우기
	Rectangle(_mdc, _mouse.x - 5, 
		_mouse.y - 5, 
		_mouse.x + 5, 
		_mouse.y + 5);


	//핑키 기준 렉트 띄우기
	Rectangle(_mdc, (LONG)x - CAMERA->getCamRc().left,
		(LONG)y - CAMERA->getCamRc().top,
		(LONG)(x + pinkyImage->GetGdiInfo()->imgWidth - CAMERA->getCamRc().left),
		(LONG)(y + pinkyImage->GetGdiInfo()->imgHeight - CAMERA->getCamRc().top));


	//핑키 이미지 띄우기
	CAMERA->CAM_FRAMERENDER(&gm, pinkyImage, x, y, 5);

	//총 이미지 띄우기(회전랜더)
	//IMAGE->render(gunImage, x, y, angle);
	IMAGE->render(gunImage, x + gunImage->GetGdiInfo()->imgWidth - CAMERA->getCamRc().left,
		y + gunImage->GetGdiInfo()->imgHeight+45 - CAMERA->getCamRc().top,
		angle*(180/PI));


	//핑키 hp감소 확인
	sprintf(debugtext, "핑키 hp : %d ,%d ,%d ,%d", hp, lightbullet, mediumbullet, heavybullet);
	TextOut(_mdc, 20, 400, debugtext, strlen(debugtext));

	//UI 렌더

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

	//플레이어 이동
	//기본 dash-> 마우스 방향에서 반대 방향으로 빨리이동
	if (!INPUT->isStayDown('W') &&
		!INPUT->isStayDown('S') &&
		!INPUT->isStayDown('A') &&
		!INPUT->isStayDown('D')) //이동조건이 아닐때
	{
		if (INPUT->isStayDown(VK_SHIFT))
		{
			//이동방향
			angle = getAngle(_mouse.x+ CAMERA->getCamRc().left,
				_mouse.y + CAMERA->getCamRc().top, x, y);

			//이동
			x += cos(angle)*speed * 2;
			y -= sin(angle)* speed * 2;

			//이미지 로딩
			if (isRight) state = DASH_L;
			else if (!isRight) state = DASH_R;

			//스테미너 감소
			st -= 1;

		}

	}


	//위
	if (INPUT->isStayDown('W'))
	{
		
		if (INPUT->isStayDown(VK_SHIFT))
		{
			//이동
			y -= speed * 2;

			//이미지 로딩
			if (isRight) state = SPRINT_R;
			else if (!isRight) state = SPRINT_L;
			//스테미너 감소
			st -= 1;

		}

		else
		{
			//이동
			y -= speed;

			//이미지 로딩
			if (isRight) state = WALK_R;
			else if (!isRight) state = WALK_L;
		}
	}

	//아래
	if (INPUT->isStayDown('S'))
	{
		if (INPUT->isStayDown(VK_SHIFT))
		{
			//이동
			y += speed * 2;

			//이미지 로딩
			if (isRight) state = SPRINT_R;
			else if (!isRight) state = SPRINT_L;

			//스테미너 감소
			st -= 1;
		}
		else
		{
			//이동
			y += speed;

			//이미지 로딩
			if (isRight) state = WALK_R;
			else if (!isRight) state = WALK_L;

		}

	}

	//왼
	if (INPUT->isStayDown('A'))
	{

		if (INPUT->isStayDown(VK_SHIFT))
		{
			//이동
			x -= speed * 2;

			//이미지 로딩
			if (isRight) state = SPRINT_R;
			else if (!isRight) state = SPRINT_L;

			//스테미너 감소
			st -= 1;
		}
		else
		{

			//이동
			x -= speed;

			//이미지 로딩
			if (isRight) state = WALK_R;
			else if (!isRight) state = WALK_L;
		}

	}

	//오
	if (INPUT->isStayDown('D'))
	{

		if (INPUT->isStayDown(VK_SHIFT))
		{
			//이동
			x += speed * 2;
			//이미지 로딩
			if (isRight) state = SPRINT_R;
			else if (!isRight) state = SPRINT_L;

			//스테미너 감소
			st -= 1;
		}
		else
		{
			//이동
			x += speed;
			//이미지 로딩
			if (isRight) state = WALK_R;
			else if (!isRight) state = WALK_L;
		}

	}

	//angle = getAngle(x, y, _mouse.x + CAMERA->getCamRc().left,
	//	_mouse.y + CAMERA->getCamRc().top);


	//melee는 midleButton눌렀을 때  
	//if (INPUT->isStayDown(VK_MBUTTON))
	//{
	//	//이동방향(핑키->마우스 방향)
	//	angle = getAngle(x, y, _mouse.x + CAMERA->getCamRc().left,
	//		_mouse.y + CAMERA->getCamRc().top);
	//
	//	//이동
	//	x += cos(angle)*speed;
	//	y -= sin(angle)* speed;
	//
	//	//이미지 로딩
	//	if (isRight) state = MELEE_R;
	//	else if (!isRight) state = MELEE_L;
	//}
	
	if (INPUT->isOnceDown(VK_LBUTTON))
	{

		//이미지 로딩
		if (isRight) state = MELEE_R;
		else if (!isRight) state = MELEE_L;
	
		
		//불렛장전
		
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
		//이미지 로딩
		if (isRight) state = MELEE_R;
		else if (!isRight) state = MELEE_L;

		count++;
		if (count % 15 == 0)
		{
			_bullet->bulletFire(bulletID, x + 40, y + 40, angle);

			heavybullet--;
		}

	}


	//불렛 재장전
	if (INPUT->isOnceDown('R'))
	{
		_bullet->bulletCharge(bulletID);
	}

	//불렛 자동장전
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


