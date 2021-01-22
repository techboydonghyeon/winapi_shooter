#include "stdafx.h"
#include "Time.h"
//----------------------------------------------
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

SINGLETON_S(Time)
//----------------------------------------------
Time::Time ()
{
	// 고정 시간 기본값 사용
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
	// 현재 시간 및 델타 타임 조정
	this->currentTime = timeGetTime();
	deltaTime = (this->currentTime - this->previousTime) * scaleTime;
}
//----------------------------------------------
void Time::TimeDelay()
{
	// 느리게 걷기
	while (deltaTime < (1.0f / frame))
		TimeCaculation();
}
//----------------------------------------------
void Time::GameTime()
{
	this->TimeCaculation();

	// 프레임 제한보다 작을때까지 감소
	if (isTimeLock)
		this->TimeDelay();
	

	// 이전 프레임을 현재 프레임으로 변경
	this->previousTime = this->currentTime;
	// 프레임 증가
	this->fpsFrameCount++;
	// 델타 프레임 증가
	this->fpsTimeElapsed +=deltaTime;
	// 월드 시간 증가
	this->worldTime += deltaTime;
	// 프레임 타임이 1초 넘으면 요소 다시초기화
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