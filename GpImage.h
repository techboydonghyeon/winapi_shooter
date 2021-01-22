#pragma once
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus")

//Gdi 플러스를 쓰는 이미지를 만들어보자
class GdiImg
{
public:
	typedef struct GpIf
	{
		Gdiplus::Image* gpImg;		//이미지
		Gdiplus::Bitmap* gpBmp;		//비트맵
		float x;					//이미지 x좌표
		float y;					//이미지 y좌표
		float imgWidth;				//이미지 가로크기
		float imgHeight;			//이미지 세로크기
		int cFrameX;				//현재 프레임X
		int cFrameY;				//현재 프레임Y
		int mFrameX;				//맥스 프레임X
		int mFrameY;				//맥스 프레임Y
		bool Direction;				//방향
		int delay;					//딜레이

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
			Direction = false;		//기본 디렉션은 왼쪽
			delay = 0;
		}
	}Gpinfo, *LP_Gpinfo;

private:
	LP_Gpinfo _gdiImgInfo;		//gdi파일 정보들


public:
	GdiImg();
	~GdiImg();

	HRESULT init(const WCHAR* fileName, int ftype);									//그냥 그림 초기화
	HRESULT init(const WCHAR* fileName, int ftype, int frameX, int direction);		//최적화 초기화 어짜피 프레임 x밖에 않쓰잖습니까??


	Gdiplus::Image* GetGimg() { return _gdiImgInfo->gpImg; }						//이미지를 빨리 내놓거라(이미지 만 가져오기) 별쓸모 없음
	Gpinfo* GetGdiInfo() { return _gdiImgInfo; }									//인포 자체를 가져오기 이게 제일 안전함
	void SetGimg(Gdiplus::Image* m) { _gdiImgInfo->gpImg = m; }						//이미지만 세팅하기 별의미 없음 나머지 값은 안들어 가서
	void SetGdiInfo(Gpinfo* gpif) { _gdiImgInfo = gpif; }							//이미지 정보 세팅해주기

	//프레임 렌더 부분 함수
	void AddFrame() { _gdiImgInfo->cFrameX++; }										//프레임을 하나 증가시킨다
	void DecreaseFrame() { _gdiImgInfo->cFrameX--; }								//프레임을 하나 감소 시키는 함수
	void ZeroFrame() { _gdiImgInfo->cFrameX = 0; }									//프레임을 0으로 만든다
	void MaxFrame() { _gdiImgInfo->cFrameX = _gdiImgInfo->mFrameX - 1; }			//프레임을 맥스로 만들어 주는 함수
	void SetDelay(int delay) { _gdiImgInfo->delay = delay; }						//딜레이를 설정한다
	void DecreaseDelay() { _gdiImgInfo->delay--; }									//딜레이를 하나 감소시킨다

	//프로토 타입 구조를 이용한 클론 함수
	GdiImg* GetClone()
	{
		//자기 자신의 정보를 가지는 복제를 생성 그리고 반환
		GdiImg* gpif = new GdiImg;
		gpif->SetGdiInfo(this->_gdiImgInfo);
		return gpif;
	}
	//이거는 메모리가 누수될 가능성이 있다. 그래도 함 써보자
};

//별거 없는 파일 종류 이넘
enum FileType
{
	Image,
	Bmp
};