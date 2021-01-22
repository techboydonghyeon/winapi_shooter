
// 시스템 
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
	// 싱글톤 인스턴스 생성

	/* SYSTEM 인스턴스 생성 */
	DATA->CreateInstance();
	TIME->CreateInstance();

	/* MANAGER 인스턴스 생성 */
	IMAGE->CreateInstance();
	OBJECT->CreateInstance();
	PHSYICS->CreateInstance();
	RENDER->CreateInstance();

	/* GAME 인스턴스 생성 */
	CAMERA->CreateInstance();
	CAMERA->Init();
	
	//  매니저 리스트 초기화
	IMAGE->Init();
	OBJECT->Init();
	PHSYICS->Init();


	//이미지 텍스트 현존하는것 모두 추가했음
	//========================================================================
	//케릭터
	DATA->importFoler("../EGver2/Txts/Characters/Character_pinky.txt");
	//이펙트
	DATA->importFoler("../EGver2/Txts/Effects/Effects_all.txt");
	//에너미
	DATA->importFoler("../EGver2/Txts/Enemy/duck2/Enemy_duck2.txt");
	DATA->importFoler("../EGver2/Txts/Enemy/kamikaze/Enemy_kamikaze.txt");
	//아이템
	DATA->importFoler("../EGver2/Txts/Items/Item_all.txt");
	//구조물
	DATA->importFoler("../EGver2/Txts/Struct/Struct_barrel.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_boxes.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_root1.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_root2.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_root3.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_root4.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_shop.txt");
	DATA->importFoler("../EGver2/Txts/Struct/Struct_teleporter.txt");
	//타일
	DATA->importFoler("../EGver2/Txts/Tiles/Spaceship/Spaceship.txt");
	//총
	DATA->importFoler("../EGver2/Txts/Weapons/Machinegun.txt");
	DATA->importFoler("../EGver2/Txts/Weapons/Pistol.txt");
	DATA->importFoler("../EGver2/Txts/Weapons/Shotgun.txt");
	//총알
	DATA->importFoler("../EGver2/Txts/Bullet/Bullet_all.txt");
	DATA->importFoler("../EGver2/Txts/Huds/Huds.txt");
	//========================================================================
	
	RENDER->Init();

	gameScene.Init();
}
//-----------------------------------------------
void Engine::Release()
{
	/* MANAGER 메모리 해제 */
	IMAGE->Release();
	OBJECT->Release();
	PHSYICS->Release();
	RENDER->Release();

	/* SYSTEM 인스턴스 해제 */
	DATA->ReleaseInstance(); // TODO : 추후 메모리 해제 ( 아직 할당된 메모리 X)
	TIME->ReleaseInstance(); // 해제할 메모리 없음

	/* MANAGER 인스턴스 해제 */
	IMAGE->ReleaseInstance();
	OBJECT->ReleaseInstance();
	PHSYICS->ReleaseInstance();
	RENDER->ReleaseInstance();

	/* GAME 인스턴스 해제 */
	CAMERA->ReleaseInstance();

	gameScene.Release();
}
//-----------------------------------------------
