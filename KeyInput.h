#pragma once
#include <bitset>
//-----------------------------------------------
// �ִ� Ű ����
#define KEYMAX 256
// Ű�� ��� ������ ����
#define STAY_DOWN 0x8000
// ������ ȣ��� �̹� ȣ�� ���̿� ���������� ���
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

	//Ű�� �ѹ��� ���� ����
	bool isOnceDown(int key);
	//Ű�� �������ٰ� ����� ����
	bool isOnceUp(int key);
	//Ű�� ��� ������ ����
	bool isStayDown(int key);
	//���Ű
	bool isToggle(int key);

};

