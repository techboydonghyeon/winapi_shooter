#include "stdafx.h"
#include "gpimageManager.h"
#include "SystemInfo.h"
//-----------------------------------------------
SINGLETON_S(gpimageManager)
//-----------------------------------------------
void gpimageManager::Init()
{
	GdiplusStartup(&gpToken, &gpInput, NULL);
}
//-----------------------------------------------
void gpimageManager::Release()
{
	GdiplusShutdown(gpToken);
}
//-----------------------------------------------

//평범한 이미지 입력할때 쓰는 함수(키값, 파일 이름(경로 포함), 파일 타입 0(이미지)~1(비트맵)
GdiImg * gpimageManager::addImg(const char * key, const WCHAR * fileName, int ftype)
{
	GdiImg* gdiImg = findImg(key);//키값으로 찾고 
	if (gdiImg)return gdiImg;//만약 찾으면 찾은거 리턴

	//없으면 만들어야지
	gdiImg = new GdiImg;
	gdiplusContainer.insert(make_pair(key, gdiImg));
	gdiImg->init(fileName, ftype);

	return gdiImg;
}

//프레임 이미지 입력할때 쓰는 함수(키값, 파일이름(경로도 포함), 파일 타입 0(이미지)~1(비트맵), 프레임 개수(max frame), 방향 0,1 좌, 우
GdiImg * gpimageManager::addImg(const char * key, const WCHAR * fileName, int ftype, int mf, int direction)
{
	GdiImg* gdiImg = findImg(key);//키값으로 찾고 
	if (gdiImg)return gdiImg;//만약 찾으면 찾은거 리턴

	//없으면 만들어야지
	gdiImg = new GdiImg;
	gdiplusContainer.insert(make_pair(key, gdiImg));
	gdiImg->init(fileName, ftype, mf, direction);

	return gdiImg;
}
//-----------------------------------------------
//키 값으로 찾아서 이미지 클래스 자체를 반환하는 함수
GdiImg * gpimageManager::findImg(const char * key)
{
	gdiplusContainerItr = gdiplusContainer.find(key);	//컨테이너 이터레이터에 찾은 거 저장
	if (gdiplusContainerItr != gdiplusContainer.end())	//값 있으면
		return gdiplusContainerItr->second;				//정보 반환
	return nullptr;
}

//키 값으로 이미지를 찾아서 들고 있는 이미지만 반환하는 함수
Gdiplus::Image* gpimageManager::findGdiImg(const char* key)
{
	return gdiplusContainer.find(key)->second->GetGimg();
}

bool gpimageManager::renderBool(Graphics * gm, GdiImg * gimg, int x, int y, int delay)
{
	GdiImg* gdig = gimg;	//임시로 사용할 gdiimg 인스턴스를 담는다

	int maxFrame;//맥스 프레임
	int cFrame;//현재 프레임

	if (gdig->GetGdiInfo()->delay == 0)

	{
		gdig->SetDelay(delay);

	}
	else
	{
		gdig->DecreaseDelay();
	}


	if (gdig->GetGdiInfo()->Direction == true)
	{
		maxFrame = gdig->GetGdiInfo()->mFrameX - 1;
		cFrame = gdig->GetGdiInfo()->cFrameX;
	}
	else
	{
		maxFrame = 0;
		cFrame = gdig->GetGdiInfo()->cFrameX;
	}


	//가장 중요한 드로우 하는 부분
	gm->DrawImage(gdig->GetGimg(),					//이미지 가져온다
		x, y,										//시작점 위치
		(int)(cFrame*gdig->GetGdiInfo()->imgWidth),	//어디부터 그릴건가
		0,											//이건 높이인데 0으로 해야된다
		(int)gdig->GetGdiInfo()->imgWidth,			//어디까지 그릴건가X
		(int)gdig->GetGdiInfo()->imgHeight,			//어디까지 그릴건가Y
		Gdiplus::UnitPixel);						//어떻게 그릴건가, 왠만하면 바꾸지 말자


	if (gdig->GetGdiInfo()->delay == 0)
	{
		if (gdig->GetGdiInfo()->Direction == true)
		{
			if (cFrame < maxFrame)
			{
				gdig->AddFrame();
				
			}
			else
			{
				gdig->ZeroFrame();
				return true;
			}
		}
		else
		{
			if (cFrame > maxFrame)
			{
				gdig->DecreaseFrame();
				
			}
			else
			{
				gdig->MaxFrame(); 
				return true;
			
			}
		}
	}
	return false;

	
}

//-----------------------------------------------
//제일 별로인 함수 차라리 밑에걸 쓰지 이걸 쓰면 깜빡거리고 난리난다 그냥 쓰지말자
GdiImg * gpimageManager::render(const char * key, int x, int y)
{
	gdiplusContainerItr = gdiplusContainer.find(key);
	//Gdiplus::Graphics gEngine();
	Gdiplus::Graphics gEngine(GetDC(_hWnd));
	gEngine.DrawImage(gdiplusContainerItr->second->GetGimg(), x, y);
	return gdiplusContainerItr->second;
}

//이미지 싱글톤으로 출력할때 유용하게 쓰일 키값 으로 찾아서 출력하는 함수
void gpimageManager::render(Graphics* gm, const char * key, int x, int y)
{
	gdiplusContainerItr = gdiplusContainer.find(key);//일단 찾는다
	gm->DrawImage(gdiplusContainerItr->second->GetGimg(), x, y);
}

//이미지를 직접 입력해 그리는 랜더 별로 쓸일은 없을것 같다
void gpimageManager::render(Graphics* gm, Gdiplus::Image* gimg, int x, int y)
{
	gm->DrawImage(gimg, x, y);
}

//이미지 클래스를 받아서 그 안에 있는 이미지를 그리는 렌더
void gpimageManager::render(Graphics* gm, GdiImg* gimg, int x, int y)
{
	gm->DrawImage(gimg->GetGimg(), x, y);
}

//프레임 렌더 1
void gpimageManager::render(Graphics * gm, const char * key, int x, int y, int delay)
{
	GdiImg* gdig = gdiplusContainer.find(key)->second;	//임시로 사용할 gdiimg 인스턴스를 담는다

	int maxFrame;//맥스 프레임
	int cFrame;//현재 프레임

	if (gdig->GetGdiInfo()->delay == 0)
	{
		gdig->SetDelay(delay);
	}
	else
	{
		gdig->DecreaseDelay();
	}

	maxFrame = gdig->GetGdiInfo()->mFrameX - 1;
	cFrame = gdig->GetGdiInfo()->cFrameX;

	//가장 중요한 드로우 하는 부분
	gm->DrawImage(gdig->GetGimg(),					//이미지 가져온다
		x, y,										//시작점 위치
		(int)(cFrame*gdig->GetGdiInfo()->imgWidth),	//어디부터 그릴건가
		0,											//이건 높이인데 0으로 해야된다
		(int)gdig->GetGdiInfo()->imgWidth,			//어디까지 그릴건가X
		(int)gdig->GetGdiInfo()->imgHeight,			//어디까지 그릴건가Y
		Gdiplus::UnitPixel);						//어떻게 그릴건가, 왠만하면 바꾸지 말자

	if (gdig->GetGdiInfo()->delay == 0)
	{
		if (cFrame < maxFrame)
		{
			gdig->AddFrame();
		}
		else
		{
			gdig->ZeroFrame();
		}
	}
}

//프레임 랜더2 리버스 랜더도 다했다 이 함수 사용할때만 리버스 랜더가 가능하다.
void gpimageManager::render(Graphics * gm, GdiImg * gimg, int x, int y, int delay)
{
	GdiImg* gdig = gimg;	//임시로 사용할 gdiimg 인스턴스를 담는다

	int maxFrame;//맥스 프레임
	int cFrame;//현재 프레임

	if (gdig->GetGdiInfo()->delay == 0)

	{
		gdig->SetDelay(delay);
	}
	else
	{
		gdig->DecreaseDelay();
	}


	if (gdig->GetGdiInfo()->Direction == true)
	{
		maxFrame = gdig->GetGdiInfo()->mFrameX - 1;
		cFrame = gdig->GetGdiInfo()->cFrameX;
	}
	else
	{
		maxFrame = 0;
		cFrame = gdig->GetGdiInfo()->cFrameX;
	}


	//가장 중요한 드로우 하는 부분
	gm->DrawImage(gdig->GetGimg(),					//이미지 가져온다
		x, y,										//시작점 위치
		(int)(cFrame*gdig->GetGdiInfo()->imgWidth),	//어디부터 그릴건가
		0,											//이건 높이인데 0으로 해야된다
		(int)gdig->GetGdiInfo()->imgWidth,			//어디까지 그릴건가X
		(int)gdig->GetGdiInfo()->imgHeight,			//어디까지 그릴건가Y
		Gdiplus::UnitPixel);						//어떻게 그릴건가, 왠만하면 바꾸지 말자


	if (gdig->GetGdiInfo()->delay == 0)
	{
		if (gdig->GetGdiInfo()->Direction == true)
		{
			if (cFrame < maxFrame)
			{
				gdig->AddFrame();
			}
			else
			{
				gdig->ZeroFrame();
			}
		}
		else
		{
			if (cFrame > maxFrame)
			{
				gdig->DecreaseFrame();
			}
			else
			{
				gdig->MaxFrame();
			}
		}
	}
}

//줌 랜더 이며 확대된 이미지를 그릴때 사용한다. 줌계수는 float 형으로 받지만 2.f 마냥 int 처럼 입력해서 쓰자
//줌 줌값은 int 만 지원하기 때문이다.
void gpimageManager::render(Graphics * gm, GdiImg * gmimg, int x, int y, float zoom)
{
	gm->DrawImage(gmimg->GetGimg(), x, y,
		(int)gmimg->GetGimg()->GetWidth()*(int)zoom,
		(int)gmimg->GetGimg()->GetHeight()*(int)zoom);
}

//타일을 그릴때 사용하는 타일 랜더 이다.
void gpimageManager::render(Graphics * gm, GdiImg * gimg, int x, int y, int idxX, int idxY)
{
	gm->DrawImage(gimg->GetGimg(), x, y, idxX * 64, idxY * 64, 64, 64, Gdiplus::UnitPixel);
}

//폰트가 있는 숫자 랜더링 할때 사용하는 렌더
void gpimageManager::NumRender(Graphics*gm, GdiImg*gimg, int x, int y, int numIdx)
{
	float width = gimg->GetGdiInfo()->imgWidth;
	float height = gimg->GetGdiInfo()->imgHeight;
	gm->DrawImage(gimg->GetGimg(), x, y, numIdx*(int)width, 0,
		(int)width, (int)height, Gdiplus::UnitPixel);
	//gm->DrawImage(gimg->GetGimg(), x, y, numIdx * 10, 0,
	//	10, 16, Gdiplus::UnitPixel);
}

//hp 바나 바 형태들을 출력할대 유용한 랜더
void gpimageManager::BarRender(Graphics* gm, GdiImg* gimg, int x, int y, int percent,int max)
{
	float width = gimg->GetGdiInfo()->imgWidth / max * percent;
	float height = gimg->GetGdiInfo()->imgHeight;

	gm->DrawImage(gimg->GetGimg(), x, y, 0, 0,
		(int)width, (int)height, Gdiplus::UnitPixel);

}

//회전 랜더이다. gm을 굳이 넘겨 줄 필요도 없다. 회전 값만 넣어 주면된다.
void gpimageManager::render( GdiImg * gimg, int x, int y, float angle)
{
	Graphics gm2(_mdc);
	Gdiplus::Matrix mat;
	mat.RotateAt(-(angle), Gdiplus::PointF((float)x, (float)y));
	gm2.SetTransform(&mat);

	gm2.DrawImage(gimg->GetGimg(), x, y);
}

//리버스 랜더엔 rotateFlip(Rotate180FlipNone) 을 사용해 보자

//void gpimageManager::render(Graphics *gm,GdiImg* gimg,int x,int y)




//-----------------------------------------------
