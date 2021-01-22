#include "stdafx.h"
#include "Kamikaze.h"


Kamikaze::Kamikaze()
{
}

Kamikaze::Kamikaze(ObjectID ID_, int x_, int y_)
{
	hp = 10;
	damage = 10;

	//ī��ī�� id�� �޾Ƽ� ī�װ��� ã�� ���ʹ� ���Ϳ� Ǫ�������� �־� x, y ��ǥ�� ī��ī�� ����
	ID = ID_, x = x_, y = y_;
	isAlive = true;
	dashCount = 0;
	frameCount = 0;
	angle = 0.f;
	speed = 25.f;
	range = 1000.f;
	width = 114.f;
	height = 94.f;
	imageRc = { (LONG)(x - width / 2), (LONG)(y - height / 2),(LONG)(x + width / 2), (LONG)(y + height / 2) };
	dash = false;
	isLeft = false;
	discover = false;
	OBJECT->CreateObject(this, ID);
	hitBox = imageRc;
}

Kamikaze::~Kamikaze()
{
}

void Kamikaze::Init()
{

}

void Kamikaze::Update()
{
	//=============================== �̹��� ==================================
	//������
	if (angle > 0 && angle <= 3.141592 / 2 || angle > 3 * 3.141592 / 2 && angle <= 2 * 3.141592)
	{
		isLeft = false;
	}
	//����
	if (angle > 3.141592 / 2 && angle <= 3 * 3.141592 / 2)
	{
		isLeft = true;
	}
	//��Ȳ�� �´� �̹��� ã��
	if (isLeft)
	{
		switch (kamiImage)
		{
		case Kamikaze::IDLE:
			sprint = IMAGE->findImg("spr_kamikaze_idle_0-sheet_left");
			break;
		case Kamikaze::WALK:
			sprint = IMAGE->findImg("spr_kamikaze_walk_0-sheet_left");
			break;
		case Kamikaze::DASH:
			sprint = IMAGE->findImg("spr_kamikaze_dash_fx_0-sheet_left");
			break;
		case Kamikaze::ATTACK:
			sprint = IMAGE->findImg("spr_kamikaze_attack_0-sheet_left");
			break;
		case Kamikaze::PRECISION:
			sprint = IMAGE->findImg("spr_kamikaze_precision2_0-sheet");
			break;
		case Kamikaze::DEATH:
			sprint = IMAGE->findImg("spr_kamikaze_death_0-sheet_left");
			break;
		default:
			break;
		}
		sprint1 = IMAGE->findImg("spr_kamikaze_dash_fx_0-sheet_left");
	}
	else
	{
		switch (kamiImage)
		{
		case Kamikaze::IDLE:
			sprint = IMAGE->findImg("spr_kamikaze_idle_0-sheet");
			break;
		case Kamikaze::WALK:
			sprint = IMAGE->findImg("spr_kamikaze_walk_0-sheet");
			break;
		case Kamikaze::DASH:
			sprint = IMAGE->findImg("spr_kamikaze_dash_fx_0-sheet");
			break;
		case Kamikaze::ATTACK:
			sprint = IMAGE->findImg("spr_kamikaze_attack_0-sheet");
			break;
		case Kamikaze::PRECISION:
			sprint = IMAGE->findImg("spr_kamikaze_precision2_0-sheet");
			break;
		case Kamikaze::DEATH:
			sprint = IMAGE->findImg("spr_kamikaze_death_0-sheet");
			break;
		default:
			break;
		}
		sprint1 = IMAGE->findImg("spr_kamikaze_dash_fx_0-sheet");
	}
	kamiImage = IDLE;
	//==========================================================================

	//================================ ������ ===================================
	dashCount++;

	this->InRange();
	//�뽬�ϴ� ���� ��
	if (dashCount % 200 == 0)
	{
		//�뽬�ϴ� ������ �÷��̾� �ޱ۰��� �޾ƿ�
		this->getAngle();
		if (discover)
		{
			dash = true;
		}
		//�뽬ī��Ʈ�� ���ڰ� �ʹ� Ŀ���� �ʵ��� ��
		if (dashCount >= 2000)
		{
			dashCount = 0;
		}
	}


	//�뽬 �Ҷ�
	if (dash)
	{
		x += cosf(angle) * speed;
		y += -sinf(angle) * speed;
		frameCount++;
		kamiImage = ATTACK;
		//ī��ī���� �����̵��ϴ� ��ó�� �Ⱥ��̰� �Ҷ�� �־���
		//�ڿ������� �뽬�ϴ� ������� ���̵���
		//�̵��Ÿ���ŭ ��� ���� ����
		//���ǵ常ŭ 6�� �̵���
		if (frameCount == 6)
		{
			dash = false;
			frameCount = 0;
		}
	}
	imageRc = { (LONG)(x - width / 2), (LONG)(y - height / 2),(LONG)(x + width / 2), (LONG)(y + height / 2) };
	hitBox = imageRc;
	//==========================================================================
	sprintf(str, "x ��ǥ: %f", x);
	sprintf(str1, "angle : %f", angle);
}

void Kamikaze::Render()
{
	Gdiplus::Graphics gm(_mdc);

	//�뽬�Ҷ� �ڿ� ȿ��(�뽬 �̹���) �ֱ�(�׸��� ���� �̹���)
	if (kamiImage == ATTACK)
	{
		CAMERA->CAM_FRAMERENDER(&gm, sprint1, cosf(3.141592 + angle) * 20 + x, -sinf(3.141592 + angle) * 20 + y, 4);
	}
	//ī��ī���� ��� �̹���
	CAMERA->CAM_FRAMERENDER(&gm, sprint, x, y, 7);


	TextOut(_mdc, 0, 100, str, strlen(str));
	TextOut(_mdc, 0, 200, str1, strlen(str1));
}

void Kamikaze::Release()
{
}

void Kamikaze::InRange()
{
	float deltaX = 0, deltaY = 0;
	float distance = 0;
	deltaX = OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().x - x;
	deltaY = OBJECT->CategorytoVector(C_PLAYER)[0]->getCenter().y - y;
	distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
	if (distance < range)
	{
		discover = true;
	}
}

void Kamikaze::ChangeImg()
{
	//sprint = IMAGE->findImg("shotgun_0");
}