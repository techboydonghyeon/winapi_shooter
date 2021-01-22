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
	ImagePool	  gdiplusContainer;			//키는 스트링이고 받는 자료는 gdi이미지인 컨테이너 ImagePool = map<string, class GdiImg*>;
	ImagePoolIter gdiplusContainerItr;	//그거의 컨테이터	 ImagePool = map<string, class GdiImg*>::iterator;
	
	
	//이제부터 작업 시작한다!
	//이코드는 옯기면 푼다
	//Gdiplus::Graphics gEngine(_mdc);

public:
	static gpimageManager* GetInstance() {
		if (instance)
			return instance;
		return nullptr;
	}

	void Init();
	void Release();

	//함수들 목록이다!
	//자세한 설명은 cpp에 쓰여져 있다.
	//yeeeeee
	//22jlfsdjflas

	//평범한 이미지 입력
	GdiImg* addImg(const char* key, const WCHAR* fileName, int ftype);

	//프레임 이미지 입력
	GdiImg* addImg(const char * key, const WCHAR * fileName, int ftype, int mf, int direction);

	//키값을 바탕으로 이미지 찾기 없으면 nullptr 반환
	GdiImg* findImg(const char* key);

	//이미지만 돌려주는 찾기 출력할때 쓰자
	Gdiplus::Image * findGdiImg(const char * key);

	//실험적 그려주기1
	void render(Graphics* gm, const char* key, int x, int y);

	//이미지로 그려주기
	void render(Graphics * gm, Gdiplus::Image * gimg, int x, int y);

	//이미지 클래스를 통한 그려주기
	void render(Graphics * gm, GdiImg * gimg, int x, int y);

	//프레임 랜더 목록들 마지막에 딜레이만 넣어주면 된다 기본적으로 루프한다
	void render(Graphics *gm, const char* key, int x, int y, int delay);

	//프레임 랜더 두번째 마지멕에 딜레이 써주는건 같다 다만 받는게 키가 아닌 이미지 이다
	void render(Graphics *gm, GdiImg* gimg, int x, int y, int delay);

	//줌 값을 입력해서 그만큼 곱해준다 안타깝게도 int 형만 지원한다 float 인이유는 오버로드 하려고... 대충 3.f 이런식으로 적어주자
	void render(Graphics* gm, GdiImg* gmimg, int x, int y, float zoom);

	//타일 랜더다 시작 좌표와 타일의 위치 좌표를 적어주면 된다.
	void render(Graphics* gm, GdiImg* gimg, int x, int y, int idxX, int idxY);

	void NumRender(Graphics * gm, GdiImg * gimg, int x, int y, int nuIdx);

	void BarRender(Graphics * gm, GdiImg* gimg, int x, int y, int percent,int max);

	//로테이트 랜더 입력한 각 만큼 회전한다 45.f 를 입력하면시계 반대 방향으로 회전한다
	void render(GdiImg* gimg, int x, int y, float angle);

	void render(Graphics *gm, Gdiplus::Image *gimg, int x, int y, int delay);

	bool renderBool(Graphics *gm, GdiImg* gimg, int x, int y, int delay);

	//싸구려 그려주기 일단 쓸모 없음
	GdiImg* render(const char* key, int x, int y);	//일반랜더 입력한 x,y 기준으로 출력


	//void render(HDC mdc, const char * key, int x, int y);


	//앞으로 기능을 추가해주자


};

