#pragma once
class Engine 
{
	static Engine* instance;
	SINGLETON_H(Engine)
private:
	SceneM gameScene;

public:
	static Engine* GetInstance() {
		if (!instance)
			instance = new Engine;
			return instance;
	}
	void Init();
	void Release();

	// ���� ���� ����
	void MainLoop();

};