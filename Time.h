#pragma once

#ifndef __TIME_H__
#define __TIME_H__

// [------------------------------------]
//#include <chrono>
#include <time.h>
#pragma region TIME_

/**************************************
 ���� ������ ����

***************************************/
const float frame = 100.0f;
#pragma endregion
// [------------------------------------]
class Time
{
private:
	// �̱��� ���� �ν��Ͻ�
	static Time* instance;
	// ������ & �Ҹ��� ����
	Time();
	~Time() {}

	/*******************************
	 �ð� ����
	********************************/
	bool isTimeLock;      // ������ ���� ����

	__int64 currentTime;  // ���� �ð�
	__int64 previousTime; // ���� �ð�
	__int64 periodFrequency; // ���� �ϵ���� �ð�

	float scaleTime;       // �ּ� �ð�
	float deltaTime;       // ������ �ð�

	unsigned long fpsFrameCount;
	unsigned long frameRate;// ������ �ӵ�
	float fpsTimeElapsed;
	float worldTime;

	char text[50];

	void TimeCaculation();
	void TimeDelay();
public:
	// ���� & ���� ���� ������ ����
	Time(const Time&) = delete;
	void operator= (const Time&) = delete;
	// �̱��� ����
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
	 ���� ���� �Լ�
	******************************/
	void GameTime();

	void ShowTime();


	// ��Ÿ Ÿ�� ��ȯ
	float GetDeltaTime() const { return deltaTime; }

};


#endif // !__TIME_H__

