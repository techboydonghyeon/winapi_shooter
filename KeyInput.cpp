#include "stdafx.h"
#include "KeyInput.h"
#include "SystemInfo.h"
//-----------------------------------------------
KeyInput* KeyInput::instance = nullptr;
//-----------------------------------------------
KeyInput::KeyInput()
{
	this->Init();
	
}
//-----------------------------------------------
KeyInput::~KeyInput()
{
	this->Release();
}
//-----------------------------------------------
KeyInput * KeyInput::GetInput()
{
	if (instance == nullptr)
	{
		instance = new KeyInput;
		return instance;
	}
	else
	{
		return instance;
	}
}
//-----------------------------------------------
void KeyInput::Init()
{
	keyUp.reset();
	keyDown.reset();
}
//-----------------------------------------------
void KeyInput::Release()
{
	if (instance == nullptr)
	{
	}
	else
	{
		delete instance;
		instance = nullptr;
	}
}
//-----------------------------------------------
bool KeyInput::isOnceDown(int key)
{
	if (GetAsyncKeyState(key) & STAY_DOWN)
	{
		if (!keyDown[key])
		{
			keyDown.set(key, true);
			return keyDown[key];
		}
	}
	else
	{
		keyDown.set(key, false);
	}

	return false;
}
//-----------------------------------------------
bool KeyInput::isOnceUp(int key)
{
	if (GetAsyncKeyState(key) & STAY_DOWN)
	{
		keyUp.set(key, true);
	}
	else
	{
		if (keyUp[key])
		{
			keyUp.set(key,false);
			return keyUp[key];
		}
	}

	return false;
}
//-----------------------------------------------
bool KeyInput::isStayDown(int key)
{
	if (GetAsyncKeyState(key) & STAY_DOWN)
	{
		return true;
	}

	return false;
}
//-----------------------------------------------
bool KeyInput::isToggle(int key)
{
	if (GetKeyState(key) & ONCE_DOWN)
	{
		return true;
	}

	return false;
}
//-----------------------------------------------