#pragma once
#include "ManagerInfo.h"
#include "UI.h"

class SceneM
{	
private:
	Object* _pinky;
	Object* _kami;
	Object* _turtle;
	Object* _bomb;
	Object* _heal_shild;
	Object* _gun;

	UI* ui;

public:
	SceneM();
	~SceneM();

	void Init();
	void Release();

	void Loop();

};