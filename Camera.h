#pragma once
class Camera
{
private:
	static Camera* instance;
	SINGLETON_H(Camera)
private:
	RECT rc; // 렌더링할 화면 크기
	int x;					// 카메라 X 좌표
	int y;					// 카메라 Y 좌표
	float zoom;				// 카메라 줌 
	bool check;				// 거리 확인 bool
	enum CAMERA_SETTING
	{
		TAGET,
		FREE
	};
	CAMERA_SETTING setting;



public:
	static Camera* GetInstance() {
		if (instance)
			return instance;
		return nullptr;
	}

	void Init();
	void CAM_RENDER(Gdiplus::Graphics* gm, string, int, int);
	void CAM_RENDER(Gdiplus::Graphics * gm, GdiImg * MEME, int x_, int y_);
	void CAM_RENDER(GdiImg * gpimg, int x, int y, float angle);
	bool CAM_RENDER_BOOL(GdiImg * gpimg, int x, int y, float angle);

	//gm 타일용
	void CAM_RENDER(string ID, int x_, int y_);// 타일 용
	void CAM_FRAMERENDER(Gdiplus::Graphics* gm, GdiImg * gpimg, int x, int y, int delay);
	bool CAM_FRAMERENDER_BOOL(Gdiplus::Graphics* gm, GdiImg * gpimg, int x, int y, int delay);
	
	void ZoomFactor();

	RECT getCamRc() { return rc; }
	//void CAM_RENDER(_mdc, int x_ int y_, int x_, int, y_);


	float getAngle(float startX, float startY, float endX, float endY);
	void SettingCamera(CAMERA_SETTING TARGET_);         // 카메라 세팅
	void SettingCamera(int xFromTarget_, int yFromTarget_);

};
