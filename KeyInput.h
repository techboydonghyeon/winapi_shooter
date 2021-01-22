#pragma once
#include <bitset>
//-----------------------------------------------
// 최대 키 개수
#define KEYMAX 256
// 키가 계속 눌려진 상태
#define STAY_DOWN 0x8000
// 지난번 호출과 이번 호출 사이에 눌려져있을 경우
#define ONCE_DOWN 0x0001
//-----------------------------------------------
class KeyInput
{
private:
	static KeyInput* instance;
	bitset<KEYMAX> keyUp;
	bitset<KEYMAX> keyDown;

public:
	KeyInput();
	~KeyInput();

	static KeyInput* GetInput();
	
	void Init();
	void Release();

	//키가 한번만 눌린 상태
	bool isOnceDown(int key);
	//키가 눌려졌다가 띄어진 상태
	bool isOnceUp(int key);
	//키가 계속 눌러진 상태
	bool isStayDown(int key);
	//토글키
	bool isToggle(int key);

};

