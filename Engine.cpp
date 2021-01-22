
// �ý��� 
#include "stdafx.h"
#include "Engine.h"
#include "SystemInfo.h"
#include "ManagerMacro.h"

SINGLETON_S(Engine)
//-----------------------------------------------
void Engine::MainLoop()
{
	while (true)
	{
		if (PeekMessage(&_Message, NULL, 0, 0, PM_REMOVE))
		{
			if (_Message.message == WM_QUIT) break;
			TranslateMessage(&_Message);
			DispatchMessage(&_Message);
		}
		else
		{
			TIME->GameTime();
			gameScene.Loop();
		}
	}
}
//-----------------------------------------------
void Engine::Init()
{
	// �̱��� �ν��Ͻ� ����

	/* SYSTEM �ν��Ͻ� ���� */
	DATA->CreateInstance();
	TIME->CreateInstance();

	/* MANAGER �ν��Ͻ� ���� */
	IMAGE->CreateInstance();
	OBJECT->CreateInstance();
	PHSYICS->CreateInstance();
	RENDER->CreateInstance();

	/* GAME �ν��Ͻ� ���� */
	CAMERA->CreateInstance();
	CAMERA->Init();
	
	//  �Ŵ��� ����Ʈ �ʱ�ȭ
	IMAGE->Init();
	OBJECT->Init();
	PHSYICS->Init();


	//�̹��� �ؽ�Ʈ �����ϴ°� ��� �߰�����
	//========================================================================
	//�ɸ���
	DATA->importFoler("../EGver2/Txts/Characters/Character_pinky.txt");
	//����Ʈ
	DATA->importFoler("../EGver2/Txts/Effects/Effects_all.txt");
	//���ʹ�
	DATA->importFoler("../EGver2/Txts/Enemy/duck2/Enemy_duck2.txt");
	DATA->importFoler("../EGver2/Txts/Enemy/kamikaze/Enemy_kamikaze.txt");
	//������
	DATA->importFoler("../EGver2/Txts/Items/Item_all.txt");
	//������
	DATA->importFoler("../EGver2/Txts/Struct/Struct_barrel.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_boxes.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_root1.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_root2.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_root3.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_root4.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_shop.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_teleporter.txt");
	//Ÿ��
	DATA->importFoler("../EGver2/Txts/Tiles/Spaceship/Spaceship.txt");
	//��
	DATA->importFoler("../EGver2/Txts/Weapons/Machinegun.txt");
	DATA->importFoler("../EGver2/Txts/Weapons/Pistol.txt");
	DATA->importFoler("../EGver2/Txts/Weapons/Shotgun.txt");
	//�Ѿ�
	DATA->importFoler("../EGver2/Txts/Bullet/Bullet_all.txt");
	DATA->importFoler("../EGver2/Txts/Huds/Huds.txt");
	//========================================================================
	
	RENDER->Init();

	gameScene.Init();
}
//-----------------------------------------------
void Engine::Release()
{
	/* MANAGER �޸� ���� */
	IMAGE->Release();
	OBJECT->Release();
	PHSYICS->Release();
	RENDER->Release();

	/* SYSTEM �ν��Ͻ� ���� */
	DATA->ReleaseInstance(); // TODO : ���� �޸� ���� ( ���� �Ҵ�� �޸� X)
	TIME->ReleaseInstance(); // ������ �޸� ����

	/* MANAGER �ν��Ͻ� ���� */
	IMAGE->ReleaseInstance();
	OBJECT->ReleaseInstance();
	PHSYICS->ReleaseInstance();
	RENDER->ReleaseInstance();

	/* GAME �ν��Ͻ� ���� */
	CAMERA->ReleaseInstance();

	gameScene.Release();
}
//-----------------------------------------------
