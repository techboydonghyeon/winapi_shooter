#include "stdafx.h"
#include "GpImage.h"
#include "SystemInfo.h"
using namespace Gdiplus;

//빌어 쳐먹을 생성자 없어도 상관없지만 있는게 깔끔하다
GdiImg::GdiImg()
{
	_gdiImgInfo = new Gpinfo;
}

//빌어 쳐먹을 소멸자 없어도 된다
GdiImg::~GdiImg() {}

//가장 평범한 이닛 그냥 GDI가 아니기에 이렇게만 써도 된다
HRESULT GdiImg::init(const WCHAR * fileName, int ftype)
{
	//이미지 정보 가지고 있던 구조체를 초기화 일단 시키자
	_gdiImgInfo = new GpIf;		//새로운 이미지 정보 객체 생성 구조체임 이거
	if (ftype == FileType::Image)
	{
		//파일타입이 이미지 일경우
		_gdiImgInfo->gpImg = Image::FromFile(fileName);
		_gdiImgInfo->imgWidth = (float)_gdiImgInfo->gpImg->GetWidth();
		_gdiImgInfo->imgHeight = (float)_gdiImgInfo->gpImg->GetHeight();
	}
	else if (ftype == FileType::Bmp)
	{
		//파일 타입이 비트맵 일 경우
		_gdiImgInfo->gpBmp = Bitmap::FromFile(fileName);
		_gdiImgInfo->imgWidth = (float)_gdiImgInfo->gpBmp->GetWidth();
		_gdiImgInfo->imgHeight = (float)_gdiImgInfo->gpBmp->GetHeight();
	}

	return S_OK;
}


HRESULT GdiImg::init(const WCHAR * fileName, int ftype, int frameX, int direction)
{
	//이미지 정보 가지고 있던 구조체를 초기화 일단 시키자
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
