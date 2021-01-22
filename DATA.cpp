#include "stdafx.h"
#include "DATA.h"
#include "ManagerInfo.h"
//#include "ManagerMacro.h"

SINGLETON_S(Data)

//폴더 이름(경로가 있다면 함께) 을 적어주면 거기 안의 이미지들을 포멧에 맞게 임포트 해주는 함수
void Data::importFoler(const char* filename)
{
	string mainLoot = "";			//txt 파일 첫번째 줄에 쓰여있는 임포트할 폴더 경로
	string imageName = "";			//이미지 이름
	string wcharStirng = "";		//임시 wstring
	char keyName[80];				//키값으로 쓰일 예정
	int fileType = 0;				//이미지 클레스 내에 정의된 그뭐냐 타입 이넘을 담을 변수 0 : 이미지 1 : 비트맵

	int isFrame = 0;				//프레임인가
	int mFrame = 0;					//프레임 개수
	int Direction = 0;				//방향


	ifstream is(filename);			//파일을 가져오기 위한 이프스트림
	if (is.is_open())
	{
		is >> mainLoot;				//일단 첫번째 줄의 메인 경로를 저장
		while (is >> keyName >> imageName >> fileType)
		{
			wcharStirng = mainLoot + imageName;	//루트 경로랑 파일 이름을 쓰까서 새 경로 생성
			wstring numGim = wstring(wcharStirng.begin(), wcharStirng.end());	//형변환을 위한 뻘짓
			is >> isFrame;														//그다음 읽는다
			if (isFrame == 1)	//만약 프레임 입력부분이 1이면 다음 실행 아니면 그냥 지금까지 읽는거 입력후 나감
			{
				is >> mFrame;		//maxframe 그냥 프레임 개수 라고 보면됨 8장이면 8 입력
				is >> Direction;	//방향 0이면 왼쪽 1이면 오른쪽이다
				IMAGE->addImg(keyName, numGim.c_str(), fileType, mFrame,Direction);//입력한 값들 바탕으로 저장
			}
			else
			{
				IMAGE->addImg(keyName, numGim.c_str(), fileType);	//형변환 된거 이미지 메니저에 값 넘기기
			}
		}
	}

}

void Data::importFolerObject(const char * filename)
{
	int ID   = 0; // 오브젝트 타입
	int posx = 0;    // x 좌표
	int posy = 0;    // y 좌표

	ifstream is(filename);			//파일을 가져오기 위한 이프스트림
	if (is.is_open())
	{
		while (is >> ID >> posx >> posy)
		{


		}
	}
}

void Data::importFolerTile(const char * filename)
{
	string ID = 0; // 오브젝트 타입
	int posx = 0;    // x 좌표
	int posy = 0;    // y 좌표

	ifstream is(filename);			//파일을 가져오기 위한 이프스트림
	if (is.is_open())
	{
		while (is >> ID >> posx >> posy)
		{
			Tile* ob = new Tile(ID, posx, posy);
		}
	}
}

void Data::Init()
{

}
