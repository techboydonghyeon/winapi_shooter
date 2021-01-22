#include "stdafx.h"
#include "GpImage.h"
#include "SystemInfo.h"
using namespace Gdiplus;

//���� �ĸ��� ������ ��� ��������� �ִ°� ����ϴ�
GdiImg::GdiImg()
{
	_gdiImgInfo = new Gpinfo;
}

//���� �ĸ��� �Ҹ��� ��� �ȴ�
GdiImg::~GdiImg() {}

//���� ����� �̴� �׳� GDI�� �ƴϱ⿡ �̷��Ը� �ᵵ �ȴ�
HRESULT GdiImg::init(const WCHAR * fileName, int ftype)
{
	//�̹��� ���� ������ �ִ� ����ü�� �ʱ�ȭ �ϴ� ��Ű��
	_gdiImgInfo = new GpIf;		//���ο� �̹��� ���� ��ü ���� ����ü�� �̰�
	if (ftype == FileType::Image)
	{
		//����Ÿ���� �̹��� �ϰ��
		_gdiImgInfo->gpImg = Image::FromFile(fileName);
		_gdiImgInfo->imgWidth = (float)_gdiImgInfo->gpImg->GetWidth();
		_gdiImgInfo->imgHeight = (float)_gdiImgInfo->gpImg->GetHeight();
	}
	else if (ftype == FileType::Bmp)
	{
		//���� Ÿ���� ��Ʈ�� �� ���
		_gdiImgInfo->gpBmp = Bitmap::FromFile(fileName);
		_gdiImgInfo->imgWidth = (float)_gdiImgInfo->gpBmp->GetWidth();
		_gdiImgInfo->imgHeight = (float)_gdiImgInfo->gpBmp->GetHeight();
	}

	return S_OK;
}


HRESULT GdiImg::init(const WCHAR * fileName, int ftype, int frameX, int direction)
{
	//�̹��� ���� ������ �ִ� ����ü�� �ʱ�ȭ �ϴ� ��Ű��
	_gdiImgInfo = new GpIf;
	_gdiImgInfo->cFrameX = 0;
	_gdiImgInfo->mFrameX = frameX;
	_gdiImgInfo->Direction = (bool)direction;
	if (ftype == FileType::Image)
	{
		_gdiImgInfo->gpImg = Image::FromFile(fileName);
		_gdiImgInfo->imgWidth = (float)_gdiImgInfo->gpImg->GetWidth() / frameX;
		_gdiImgInfo->imgHeight = (float)_gdiImgInfo->gpImg->GetHeight();
	}
	else if (ftype == FileType::Bmp)
	{
		_gdiImgInfo->gpBmp = Bitmap::FromFile(fileName);
		_gdiImgInfo->imgWidth = (float)_gdiImgInfo->gpBmp->GetWidth() / frameX;
		_gdiImgInfo->imgHeight = (float)_gdiImgInfo->gpBmp->GetHeight();
	}

	return S_OK;
}
