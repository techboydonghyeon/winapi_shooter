#include "stdafx.h"
#include "RenderM.h"
#include "SystemInfo.h"
#include "ManagerMacro.h"
SINGLETON_S(RenderM)


//-------------------------------------------
void RenderM::RenderGame()
{
	InvalidateRect(_hWnd, NULL, FALSE);
	ShowMsgBox(0);
	Gdiplus::Graphics gm(_mdc);	//�׸��� �ʿ��� ��
	//-------------------------------------------

	//CAMERA->CAM_RENDER(&gm,"pinky_dash_left", 300, 300);
	//CAMERA->CAM_RENDER(&gm,"pistol_0", 400, 200);
	//IMAGE->render(&gm, "pinky_sprint_right", 100, 100, 5);
	//IMAGE->render(&gm, IMAGE->findImg("pinky_death_right"), 200, 100, 5);

	OBJECT->RenderTile();
	OBJECT->RenderObject();
	TIME->ShowTime();

	//-------------------------------------------
	BitBlt(_hdc, 0, 0, _WINSIZEX, _WINSIZEY, _mdc, 0, 0, SRCCOPY);
}


//GUN gun;
//ObjectID bulletID;

void RenderM::RenderGame(UI* ui)
{
	InvalidateRect(_hWnd, NULL, FALSE);
	ShowMsgBox(0);
	Gdiplus::Graphics gm(_mdc);	//�׸��� �ʿ��� ��
	//-------------------------------------------
	ui->ShowHpBar(&gm, DATA->getPlaya()->getHp(),200, DATA->getPlaya()->getShild(), 200,
	DATA->getPlaya()->getSt(), 200);
	
	ui->ShowBounty(&gm, DATA->getPlaya()->GetBounty());
	ui->ShowGun(&gm, dynamic_cast<Pinky*>(DATA->getPlaya())->GetGun(),
		dynamic_cast<Bullet*>(DATA->getBullet())->GetMagazineNum(),
		dynamic_cast<Bullet*>(DATA->getBullet())->GetBulletNum(), 300);




	//pistol
	ui->ShowGun(&gm, dynamic_cast<Pinky*>(DATA->getPlaya())->GetGun(),
		dynamic_cast<Bullet*>(DATA->getBullet())->GetMagazineSingle(),
		dynamic_cast<Bullet*>(DATA->getBullet())->GetBulletNumSingle(), 300);


	//shotgun
	//ui->ShowGun(&gm, dynamic_cast<Pinky*>(DATA->getPlaya())->GetGun(),
	//	dynamic_cast<Bullet*>(DATA->getBullet())->GetMagazineShotGun(),
	//	dynamic_cast<Bullet*>(DATA->getBullet())->GetBulletNumShotGun(), 300);
	

	//machingun
	//ui->ShowGun(&gm, dynamic_cast<Pinky*>(DATA->getPlaya())->GetGun(),
	//	dynamic_cast<Bullet*>(DATA->getBullet())->GetMagazineAuto(),
	//	dynamic_cast<Bullet*>(DATA->getBullet())->GetBulletNumAuto(), 300);
		






	




	
	//	dynamic_cast<Bullet*>(DATA->getBullet()->, 50, 300);
	//dynamic_cast<Bullet*>(DATA->getBullet())->	, int leftamo, int maxamo);
	//ui->ShowGun(&gm, 1, 250, 50, 300);
		//dynamic_cast<Bullet*>(DATA->getBullet())->	, int leftamo, int maxamo);
	//ui->ShowGun(&gm, int gunName, int amo, int leftamo, int maxamo);
	//�μ� ��� �״�� ���� hp, �ִ� hp ���� ����, �ִ� ���带 ��������
	//void UI::ShowHpBar(Graphics* gm, int hp, int maxhp, int shield, int maxshield, int st, int maxSt)
	//hp ��,���� ��, ���¸ӳ� �� �� �����ִ� �Լ� �׳� ���̴� ��� �Է��ϸ� �ȴ�.
	//void ShowHpBar(Graphics * gm, int hp, int maxhp, int shield, int maxshield, int st, int maxSt);
	////���� �Է��ϸ� ����� �ش�.
	//void ShowBounty(Graphics * gm, int bounty);
	////�� �̳Ѱ��̶� ���� �Ѿ˼�, ���� �Ѿ� ��, �ִ� �Ѿ� ���� �Է��� ����.
	//void ShowGun(Graphics * gm, int gunName, int amo, int leftamo, int maxamo);

	OBJECT->RenderTile();
	OBJECT->RenderObject();
	TIME->ShowTime();

	//-------------------------------------------
	BitBlt(_hdc, 0, 0, _WINSIZEX, _WINSIZEY, _mdc, 0, 0, SRCCOPY);
}
//-------------------------------------------
void RenderM::Init()
{
	// ȭ�鿡 �׷��� DC
	_hdc = GetDC(_hWnd);
	_mdc = CreateCompatibleDC(_hdc);
	hBit = (HBITMAP)CreateCompatibleBitmap(_hdc, _WINSIZEX, _WINSIZEY);
	hOBit = (HBITMAP)SelectObject(_mdc, hBit);
	CreateMsgBox(0, 0, _WINSIZEX, _WINSIZEY, 102, 102, 102);
}
//-------------------------------------------
void RenderM::Release()
{
	// ȭ�� �� �޸� DC ����
	ReleaseDC(_hWnd, _hdc);
	ReleaseDC(_hWnd, _mdc);
	SelectObject(_mdc, hOBit);
	DeleteObject(hBit);
	DeleteDC(_mdc);
	for (UINT i = 0; i < boxPool.size(); ++i){
		delete boxPool[i];
		boxPool[i] = nullptr;
	}
}
//-------------------------------------------
void RenderM::CreateMsgBox(
	LONG left, LONG top, LONG right, LONG bottom, // ����ü
	int r, int g, int b)                          // RGB��
{
	MSG_BOX* box = new MSG_BOX;
	box->rc = { left,top,right,bottom };
	box->bit = CreateSolidBrush(RGB(r, g, b));
	box->obit = (HBRUSH)SelectObject(_mdc, box->bit);
	boxPool.push_back(box);
}
//-------------------------------------------
void RenderM::ShowMsgBox(int p)
{
	if(boxPool.size() > p)
	FillRect(_mdc, &boxPool[p]->rc, boxPool[p]->bit);
}
//-------------------------------------------