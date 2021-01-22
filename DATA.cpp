#include "stdafx.h"
#include "DATA.h"
#include "ManagerInfo.h"
//#include "ManagerMacro.h"

SINGLETON_S(Data)

//���� �̸�(��ΰ� �ִٸ� �Բ�) �� �����ָ� �ű� ���� �̹������� ���信 �°� ����Ʈ ���ִ� �Լ�
void Data::importFoler(const char* filename)
{
	string mainLoot = "";			//txt ���� ù��° �ٿ� �����ִ� ����Ʈ�� ���� ���
	string imageName = "";			//�̹��� �̸�
	string wcharStirng = "";		//�ӽ� wstring
	char keyName[80];				//Ű������ ���� ����
	int fileType = 0;				//�̹��� Ŭ���� ���� ���ǵ� �׹��� Ÿ�� �̳��� ���� ���� 0 : �̹��� 1 : ��Ʈ��

	int isFrame = 0;				//�������ΰ�
	int mFrame = 0;					//������ ����
	int Direction = 0;				//����


	ifstream is(filename);			//������ �������� ���� ������Ʈ��
	if (is.is_open())
	{
		is >> mainLoot;				//�ϴ� ù��° ���� ���� ��θ� ����
		while (is >> keyName >> imageName >> fileType)
		{
			wcharStirng = mainLoot + imageName;	//��Ʈ ��ζ� ���� �̸��� ��� �� ��� ����
			wstring numGim = wstring(wcharStirng.begin(), wcharStirng.end());	//����ȯ�� ���� ����
			is >> isFrame;														//�״��� �д´�
			if (isFrame == 1)	//���� ������ �Էºκ��� 1�̸� ���� ���� �ƴϸ� �׳� ���ݱ��� �д°� �Է��� ����
			{
				is >> mFrame;		//maxframe �׳� ������ ���� ��� ����� 8���̸� 8 �Է�
				is >> Direction;	//���� 0�̸� ���� 1�̸� �������̴�
				IMAGE->addImg(keyName, numGim.c_str(), fileType, mFrame,Direction);//�Է��� ���� �������� ����
			}
			else
			{
				IMAGE->addImg(keyName, numGim.c_str(), fileType);	//����ȯ �Ȱ� �̹��� �޴����� �� �ѱ��
			}
		}
	}

}

void Data::importFolerObject(const char * filename)
{
	int ID   = 0; // ������Ʈ Ÿ��
	int posx = 0;    // x ��ǥ
	int posy = 0;    // y ��ǥ

	ifstream is(filename);			//������ �������� ���� ������Ʈ��
	if (is.is_open())
	{
		while (is >> ID >> posx >> posy)
		{


		}
	}
}

void Data::importFolerTile(const char * filename)
{
	string ID = 0; // ������Ʈ Ÿ��
	int posx = 0;    // x ��ǥ
	int posy = 0;    // y ��ǥ

	ifstream is(filename);			//������ �������� ���� ������Ʈ��
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
