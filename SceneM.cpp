#include "stdafx.h"
#include "SceneM.h"
#include "ManagerMacro.h"
//-------------------------------------------
SceneM::SceneM()
{
	
}
//-------------------------------------------
SceneM::~SceneM()
{
}
//-------------------------------------------
void SceneM::Init()
{
	_pinky = new Pinky(P_PINKY, 200, 200);
	_kami = new Kamikaze(E_KAMIKAZE, _WINSIZEX / 2, _WINSIZEY / 2);
	_turtle = new Turtle(E_DUCK, 300, 300);
	_bomb = new Bomb(I_BOMB, 500, 20);
	_heal_shild = new HealandShild(I_HEAL_SHILD, 500, 300);
	_gun = new Gun(I_GUN, 700, 300);
	ui = new UI;
	ui->Init();
}
//-------------------------------------------
void SceneM::Release()
{

}
//-------------------------------------------
void SceneM::Loop()
{
	CAMERA->ZoomFactor();
	OBJECT->UpdateObject();
	PHSYICS->PhsyicsGame();
	RENDER->RenderGame(ui);
}
//-------------------------------------------