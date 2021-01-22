#pragma once
class PhsyicsM
{
private:
	SINGLETON_H(PhsyicsM)
	static PhsyicsM* instance;
public:
	static PhsyicsM* GetInstance() {
		if (instance)
			return instance;
		return nullptr;
	}
	void Init();
	void Release();

	void PhsyicsGame();
};

