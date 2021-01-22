#pragma once
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus")

//Gdi �÷����� ���� �̹����� ������
class GdiImg
{
public:
	typedef struct GpIf
	{
		Gdiplus::Image* gpImg;		//�̹���
		Gdiplus::Bitmap* gpBmp;		//��Ʈ��
		float x;					//�̹��� x��ǥ
		float y;					//�̹��� y��ǥ
		float imgWidth;				//�̹��� ����ũ��
		float imgHeight;			//�̹��� ����ũ��
		int cFrameX;				//���� ������X
		int cFrameY;				//���� ������Y
		int mFrameX;				//�ƽ� ������X
		int mFrameY;				//�ƽ� ������Y
		bool Direction;				//����
		int delay;					//������

		GpIf()
		{
			gpImg = nullptr;
			gpBmp = nullptr;
			x = 0;
			y = 0;
			imgWidth = 0;
			imgHeight = 0;
			cFrameX = 0;
			cFrameY = 0;
			mFrameX = 0;
			mFrameY = 0;
			Direction = false;		//�⺻ �𷺼��� ����
			delay = 0;
		}
	}Gpinfo, *LP_Gpinfo;

private:
	LP_Gpinfo _gdiImgInfo;		//gdi���� ������


public:
	GdiImg();
	~GdiImg();

	HRESULT init(const WCHAR* fileName, int ftype);									//�׳� �׸� �ʱ�ȭ
	HRESULT init(const WCHAR* fileName, int ftype, int frameX, int direction);		//����ȭ �ʱ�ȭ ��¥�� ������ x�ۿ� �ʾ��ݽ��ϱ�??


	Gdiplus::Image* GetGimg() { return _gdiImgInfo->gpImg; }						//�̹����� ���� �����Ŷ�(�̹��� �� ��������) ������ ����
	Gpinfo* GetGdiInfo() { return _gdiImgInfo; }									//���� ��ü�� �������� �̰� ���� ������
	void SetGimg(Gdiplus::Image* m) { _gdiImgInfo->gpImg = m; }						//�̹����� �����ϱ� ���ǹ� ���� ������ ���� �ȵ�� ����
	void SetGdiInfo(Gpinfo* gpif) { _gdiImgInfo = gpif; }							//�̹��� ���� �������ֱ�

	//������ ���� �κ� �Լ�
	void AddFrame() { _gdiImgInfo->cFrameX++; }										//�������� �ϳ� ������Ų��
	void DecreaseFrame() { _gdiImgInfo->cFrameX--; }								//�������� �ϳ� ���� ��Ű�� �Լ�
	void ZeroFrame() { _gdiImgInfo->cFrameX = 0; }									//�������� 0���� �����
	void MaxFrame() { _gdiImgInfo->cFrameX = _gdiImgInfo->mFrameX - 1; }			//�������� �ƽ��� ����� �ִ� �Լ�
	void SetDelay(int delay) { _gdiImgInfo->delay = delay; }						//�����̸� �����Ѵ�
	void DecreaseDelay() { _gdiImgInfo->delay--; }									//�����̸� �ϳ� ���ҽ�Ų��

	//������ Ÿ�� ������ �̿��� Ŭ�� �Լ�
	GdiImg* GetClone()
	{
		//�ڱ� �ڽ��� ������ ������ ������ ���� �׸��� ��ȯ
		GdiImg* gpif = new GdiImg;
		gpif->SetGdiInfo(this->_gdiImgInfo);
		return gpif;
	}
	//�̰Ŵ� �޸𸮰� ������ ���ɼ��� �ִ�. �׷��� �� �Ẹ��
};

//���� ���� ���� ���� �̳�
enum FileType
{
	Image,
	Bmp
};