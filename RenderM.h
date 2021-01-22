#pragma once
#include "UI.h"

struct MSG_BOX
{
	RECT rc;
	HBRUSH bit;
	HBRUSH obit;
};
class RenderM
{
private:
	static RenderM* instance;
	SINGLETON_H(RenderM)
private:
	vector<MSG_BOX*>boxPool;
	HBITMAP hBit;
	HBITMAP hOBit;


public:
	static RenderM* GetInstance() {
		if (instance)
			return instance;
		return nullptr;
	}
	void Init();
	void Release();

	void RenderGame();
	void RenderGame(UI* ui);

	void CreateMsgBox(LONG left, LONG top, LONG right, LONG bottom,int r, int g, int b);
	void ShowMsgBox(int);
};