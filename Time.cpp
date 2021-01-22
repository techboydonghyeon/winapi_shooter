#include "stdafx.h"
#include "Time.h"
//----------------------------------------------
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

SINGLETON_S(Time)
//----------------------------------------------
Time::Time ()
{
	// ���� �ð� �⺻�� ���
	isTimeLock = true;

	this->previousTime = timeGetTime();
	this->scaleTime = 0.001f;

	this->fpsTimeElapsed = 0.0f;
	this->worldTime = 0.0f;
	deltaTime = 0.0f;

	this->frameRate = 0;
	this->fpsFrameCount = 0;
}
//----------------------------------------------
void Time::TimeCaculation()
{
	// ���� �ð� �� ��Ÿ Ÿ�� ����
	this->currentTime = timeGetTime();
	deltaTime = (this->currentTime - this->previousTime) * scaleTime;
}
//----------------------------------------------
void Time::TimeDelay()
{
	// ������ �ȱ�
	while (deltaTime < (1.0f / frame))
		TimeCaculation();
}
//----------------------------------------------
void Time::GameTime()
{
	this->TimeCaculation();

	// ������ ���Ѻ��� ���������� ����
	if (isTimeLock)
		this->TimeDelay();
	

	// ���� �������� ���� ���������� ����
	this->previousTime = this->currentTime;
	// ������ ����
	this->fpsFrameCount++;
	// ��Ÿ ������ ����
	this->fpsTimeElapsed +=deltaTime;
	// ���� �ð� ����
	this->worldTime += deltaTime;
	// ������ Ÿ���� 1�� ������ ��� �ٽ��ʱ�ȭ
	if (this->fpsTimeElapsed > 1.0f)
	{
		this->frameRate = this->fpsFrameCount;
		this->fpsFrameCount = 0;
		this->fpsTimeElapsed = 0.0f;
	}
}
//----------------------------------------------
static const int _DEBUG_SIZE = 25;

void Time::ShowTime()
{
#ifdef _DEBUG
	SetBkColor(_mdc, RGB(102,102,204));
	sprintf(text, "@FrameRate : %d", frameRate);
	TextOut(_mdc, _DEBUG_SIZE, _DEBUG_SIZE, text, (int)strlen(text));
	sprintf(text, "@DeltaTime : %f", deltaTime);
	TextOut(_mdc, _DEBUG_SIZE, _DEBUG_SIZE*2, text, (int)strlen(text));
	sprintf(text, "@WorldTime : %f", worldTime);
	TextOut(_mdc, _DEBUG_SIZE, _DEBUG_SIZE*3, text, (int)strlen(text));
#endif // !_DEBUG
}

//----------------------------------------------