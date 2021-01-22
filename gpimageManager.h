#pragma once
#include"GpImage.h"
#include "Define.h"
#include "Management.h"
using namespace Management;

class gpimageManager
{
private:
	static gpimageManager* instance;
	SINGLETON_H(gpimageManager)
	ImagePool	  gdiplusContainer;			//Ű�� ��Ʈ���̰� �޴� �ڷ�� gdi�̹����� �����̳� ImagePool = map<string, class GdiImg*>;
	ImagePoolIter gdiplusContainerItr;	//�װ��� ��������	 ImagePool = map<string, class GdiImg*>::iterator;
	
	
	//�������� �۾� �����Ѵ�!
	//���ڵ�� ����� Ǭ��
	//Gdiplus::Graphics gEngine(_mdc);

public:
	static gpimageManager* GetInstance() {
		if (instance)
			return instance;
		return nullptr;
	}

	void Init();
	void Release();

	//�Լ��� ����̴�!
	//�ڼ��� ������ cpp�� ������ �ִ�.
	//yeeeeee
	//22jlfsdjflas

	//����� �̹��� �Է�
	GdiImg* addImg(const char* key, const WCHAR* fileName, int ftype);

	//������ �̹��� �Է�
	GdiImg* addImg(const char * key, const WCHAR * fileName, int ftype, int mf, int direction);

	//Ű���� �������� �̹��� ã�� ������ nullptr ��ȯ
	GdiImg* findImg(const char* key);

	//�̹����� �����ִ� ã�� ����Ҷ� ����
	Gdiplus::Image * findGdiImg(const char * key);

	//������ �׷��ֱ�1
	void render(Graphics* gm, const char* key, int x, int y);

	//�̹����� �׷��ֱ�
	void render(Graphics * gm, Gdiplus::Image * gimg, int x, int y);

	//�̹��� Ŭ������ ���� �׷��ֱ�
	void render(Graphics * gm, GdiImg * gimg, int x, int y);

	//������ ���� ��ϵ� �������� �����̸� �־��ָ� �ȴ� �⺻������ �����Ѵ�
	void render(Graphics *gm, const char* key, int x, int y, int delay);

	//������ ���� �ι�° �����߿� ������ ���ִ°� ���� �ٸ� �޴°� Ű�� �ƴ� �̹��� �̴�
	void render(Graphics *gm, GdiImg* gimg, int x, int y, int delay);

	//�� ���� �Է��ؼ� �׸�ŭ �����ش� ��Ÿ���Ե� int ���� �����Ѵ� float �������� �����ε� �Ϸ���... ���� 3.f �̷������� ��������
	void render(Graphics* gm, GdiImg* gmimg, int x, int y, float zoom);

	//Ÿ�� ������ ���� ��ǥ�� Ÿ���� ��ġ ��ǥ�� �����ָ� �ȴ�.
	void render(Graphics* gm, GdiImg* gimg, int x, int y, int idxX, int idxY);

	void NumRender(Graphics * gm, GdiImg * gimg, int x, int y, int nuIdx);

	void BarRender(Graphics * gm, GdiImg* gimg, int x, int y, int percent,int max);

	//������Ʈ ���� �Է��� �� ��ŭ ȸ���Ѵ� 45.f �� �Է��ϸ�ð� �ݴ� �������� ȸ���Ѵ�
	void render(GdiImg* gimg, int x, int y, float angle);

	void render(Graphics *gm, Gdiplus::Image *gimg, int x, int y, int delay);

	bool renderBool(Graphics *gm, GdiImg* gimg, int x, int y, int delay);

	//�α��� �׷��ֱ� �ϴ� ���� ����
	GdiImg* render(const char* key, int x, int y);	//�Ϲݷ��� �Է��� x,y �������� ���


	//void render(HDC mdc, const char * key, int x, int y);


	//������ ����� �߰�������


};

