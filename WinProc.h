#pragma once
class WinProc
{
private:
	WNDCLASS WndClass;

public:
	WinProc();
	WinProc(HINSTANCE,int);
	~WinProc();
};

