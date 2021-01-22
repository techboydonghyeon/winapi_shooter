#pragma once

#ifndef __TIME_H__
#define __TIME_H__

// [------------------------------------]
//#include <chrono>
#include <time.h>
#pragma region TIME_

/**************************************
 게임 프레임 고정

***************************************/
const float frame = 100.0f;
#pragma endregion
// [------------------------------------]
class Time
{
private:
	// 싱글턴 고유 인스턴스
	static Time* instance;
	// 생성자 & 소멸자 숨김
	Time();
	~Time() {}

	/*******************************
	 시간 변수
	********************************/
	bool isTimeLock;      // 프레임 고정 여부

	__int64 currentTime;  // 현재 시간
	__int64 previousTime; // 이전 시간
	__int64 periodFrequency; // 고성능 하드웨어 시간

	float scaleTime;       // 최소 시간
	float deltaTime;       // 보정된 시간

	unsigned long fpsFrameCount;
	unsigned long frameRate;// 프레임 속도
	float fpsTimeElapsed;
	float worldTime;

	char text[50];

	void TimeCaculation();
	void TimeDelay();
public:
	// 복사 & 복사 대입 생성자 제거
	Time(const Time&) = delete;
	void operator= (const Time&) = delete;
	// 싱글턴 구현
	static Time* GetInstance() {
		return instance == nullptr ? nullptr : instance;
	}
	static void ReleaseInstance() {
		if (instance) delete instance; instance = nullptr;
	}
	static void CreateInstance() {
		if (!instance) instance = new Time;
	}

	/******************************
	 게임 진행 함수
	******************************/
	void GameTime();

	void ShowTime();


	// 델타 타임 반환
	float GetDeltaTime() const { return deltaTime; }

};


#endif // !__TIME_H__

