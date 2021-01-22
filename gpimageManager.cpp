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

//����� �̹��� �Է��Ҷ� ���� �Լ�(Ű��, ���� �̸�(��� ����), ���� Ÿ�� 0(�̹���)~1(��Ʈ��)
GdiImg * gpimageManager::addImg(const char * key, const WCHAR * fileName, int ftype)
{
	GdiImg* gdiImg = findImg(key);//Ű������ ã�� 
	if (gdiImg)return gdiImg;//���� ã���� ã���� ����

	//������ ��������
	gdiImg = new GdiImg;
	gdiplusContainer.insert(make_pair(key, gdiImg));
	gdiImg->init(fileName, ftype);

	return gdiImg;
}

//������ �̹��� �Է��Ҷ� ���� �Լ�(Ű��, �����̸�(��ε� ����), ���� Ÿ�� 0(�̹���)~1(��Ʈ��), ������ ����(max frame), ���� 0,1 ��, ��
GdiImg * gpimageManager::addImg(const char * key, const WCHAR * fileName, int ftype, int mf, int direction)
{
	GdiImg* gdiImg = findImg(key);//Ű������ ã�� 
	if (gdiImg)return gdiImg;//���� ã���� ã���� ����

	//������ ��������
	gdiImg = new GdiImg;
	gdiplusContainer.insert(make_pair(key, gdiImg));
	gdiImg->init(fileName, ftype, mf, direction);

	return gdiImg;
}
//-----------------------------------------------
//Ű ������ ã�Ƽ� �̹��� Ŭ���� ��ü�� ��ȯ�ϴ� �Լ�
GdiImg * gpimageManager::findImg(const char * key)
{
	gdiplusContainerItr = gdiplusContainer.find(key);	//�����̳� ���ͷ����Ϳ� ã�� �� ����
	if (gdiplusContainerItr != gdiplusContainer.end())	//�� ������
		return gdiplusContainerItr->second;				//���� ��ȯ
	return nullptr;
}

//Ű ������ �̹����� ã�Ƽ� ��� �ִ� �̹����� ��ȯ�ϴ� �Լ�
Gdiplus::Image* gpimageManager::findGdiImg(const char* key)
{
	return gdiplusContainer.find(key)->second->GetGimg();
}

bool gpimageManager::renderBool(Graphics * gm, GdiImg * gimg, int x, int y, int delay)
{
	GdiImg* gdig = gimg;	//�ӽ÷� ����� gdiimg �ν��Ͻ��� ��´�

	int maxFrame;//�ƽ� ������
	int cFrame;//���� ������

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


	//���� �߿��� ��ο� �ϴ� �κ�
	gm->DrawImage(gdig->GetGimg(),					//�̹��� �����´�
		x, y,										//������ ��ġ
		(int)(cFrame*gdig->GetGdiInfo()->imgWidth),	//������ �׸��ǰ�
		0,											//�̰� �����ε� 0���� �ؾߵȴ�
		(int)gdig->GetGdiInfo()->imgWidth,			//������ �׸��ǰ�X
		(int)gdig->GetGdiInfo()->imgHeight,			//������ �׸��ǰ�Y
		Gdiplus::UnitPixel);						//��� �׸��ǰ�, �ظ��ϸ� �ٲ��� ����


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
//���� ������ �Լ� ���� �ؿ��� ���� �̰� ���� �����Ÿ��� �������� �׳� ��������
GdiImg * gpimageManager::render(const char * key, int x, int y)
{
	gdiplusContainerItr = gdiplusContainer.find(key);
	//Gdiplus::Graphics gEngine();
	Gdiplus::Graphics gEngine(GetDC(_hWnd));
	gEngine.DrawImage(gdiplusContainerItr->second->GetGimg(), x, y);
	return gdiplusContainerItr->second;
}

//�̹��� �̱������� ����Ҷ� �����ϰ� ���� Ű�� ���� ã�Ƽ� ����ϴ� �Լ�
void gpimageManager::render(Graphics* gm, const char * key, int x, int y)
{
	gdiplusContainerItr = gdiplusContainer.find(key);//�ϴ� ã�´�
	gm->DrawImage(gdiplusContainerItr->second->GetGimg(), x, y);
}

//�̹����� ���� �Է��� �׸��� ���� ���� ������ ������ ����
void gpimageManager::render(Graphics* gm, Gdiplus::Image* gimg, int x, int y)
{
	gm->DrawImage(gimg, x, y);
}

//�̹��� Ŭ������ �޾Ƽ� �� �ȿ� �ִ� �̹����� �׸��� ����
void gpimageManager::render(Graphics* gm, GdiImg* gimg, int x, int y)
{
	gm->DrawImage(gimg->GetGimg(), x, y);
}

//������ ���� 1
void gpimageManager::render(Graphics * gm, const char * key, int x, int y, int delay)
{
	GdiImg* gdig = gdiplusContainer.find(key)->second;	//�ӽ÷� ����� gdiimg �ν��Ͻ��� ��´�

	int maxFrame;//�ƽ� ������
	int cFrame;//���� ������

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

	//���� �߿��� ��ο� �ϴ� �κ�
	gm->DrawImage(gdig->GetGimg(),					//�̹��� �����´�
		x, y,										//������ ��ġ
		(int)(cFrame*gdig->GetGdiInfo()->imgWidth),	//������ �׸��ǰ�
		0,											//�̰� �����ε� 0���� �ؾߵȴ�
		(int)gdig->GetGdiInfo()->imgWidth,			//������ �׸��ǰ�X
		(int)gdig->GetGdiInfo()->imgHeight,			//������ �׸��ǰ�Y
		Gdiplus::UnitPixel);						//��� �׸��ǰ�, �ظ��ϸ� �ٲ��� ����

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

//������ ����2 ������ ������ ���ߴ� �� �Լ� ����Ҷ��� ������ ������ �����ϴ�.
void gpimageManager::render(Graphics * gm, GdiImg * gimg, int x, int y, int delay)
{
	GdiImg* gdig = gimg;	//�ӽ÷� ����� gdiimg �ν��Ͻ��� ��´�

	int maxFrame;//�ƽ� ������
	int cFrame;//���� ������

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


	//���� �߿��� ��ο� �ϴ� �κ�
	gm->DrawImage(gdig->GetGimg(),					//�̹��� �����´�
		x, y,										//������ ��ġ
		(int)(cFrame*gdig->GetGdiInfo()->imgWidth),	//������ �׸��ǰ�
		0,											//�̰� �����ε� 0���� �ؾߵȴ�
		(int)gdig->GetGdiInfo()->imgWidth,			//������ �׸��ǰ�X
		(int)gdig->GetGdiInfo()->imgHeight,			//������ �׸��ǰ�Y
		Gdiplus::UnitPixel);						//��� �׸��ǰ�, �ظ��ϸ� �ٲ��� ����


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

//�� ���� �̸� Ȯ��� �̹����� �׸��� ����Ѵ�. �ܰ���� float ������ ������ 2.f ���� int ó�� �Է��ؼ� ����
//�� �ܰ��� int �� �����ϱ� �����̴�.
void gpimageManager::render(Graphics * gm, GdiImg * gmimg, int x, int y, float zoom)
{
	gm->DrawImage(gmimg->GetGimg(), x, y,
		(int)gmimg->GetGimg()->GetWidth()*(int)zoom,
		(int)gmimg->GetGimg()->GetHeight()*(int)zoom);
}

//Ÿ���� �׸��� ����ϴ� Ÿ�� ���� �̴�.
void gpimageManager::render(Graphics * gm, GdiImg * gimg, int x, int y, int idxX, int idxY)
{
	gm->DrawImage(gimg->GetGimg(), x, y, idxX * 64, idxY * 64, 64, 64, Gdiplus::UnitPixel);
}

//��Ʈ�� �ִ� ���� ������ �Ҷ� ����ϴ� ����
void gpimageManager::NumRender(Graphics*gm, GdiImg*gimg, int x, int y, int numIdx)
{
	float width = gimg->GetGdiInfo()->imgWidth;
	float height = gimg->GetGdiInfo()->imgHeight;
	gm->DrawImage(gimg->GetGimg(), x, y, numIdx*(int)width, 0,
		(int)width, (int)height, Gdiplus::UnitPixel);
	//gm->DrawImage(gimg->GetGimg(), x, y, numIdx * 10, 0,
	//	10, 16, Gdiplus::UnitPixel);
}

//hp �ٳ� �� ���µ��� ����Ҵ� ������ ����
void gpimageManager::BarRender(Graphics* gm, GdiImg* gimg, int x, int y, int percent,int max)
{
	float width = gimg->GetGdiInfo()->imgWidth / max * percent;
	float height = gimg->GetGdiInfo()->imgHeight;

	gm->DrawImage(gimg->GetGimg(), x, y, 0, 0,
		(int)width, (int)height, Gdiplus::UnitPixel);

}

//ȸ�� �����̴�. gm�� ���� �Ѱ� �� �ʿ䵵 ����. ȸ�� ���� �־� �ָ�ȴ�.
void gpimageManager::render( GdiImg * gimg, int x, int y, float angle)
{
	Graphics gm2(_mdc);
	Gdiplus::Matrix mat;
	mat.RotateAt(-(angle), Gdiplus::PointF((float)x, (float)y));
	gm2.SetTransform(&mat);

	gm2.DrawImage(gimg->GetGimg(), x, y);
}

//������ ������ rotateFlip(Rotate180FlipNone) �� ����� ����

//void gpimageManager::render(Graphics *gm,GdiImg* gimg,int x,int y)




//-----------------------------------------------
