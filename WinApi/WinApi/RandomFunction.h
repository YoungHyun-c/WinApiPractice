#pragma once
// RandomFunction
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		// API ���� �Լ�.
		// GetTickCount(): API �Լ��� OS�� ���õ� ���� ��� �ð��� üũ.
		// ������ �и� ���� -> �и� ���� �����̱� ������ �Ը� ũ�� �ʴ� ������ ����.
		srand(GetTickCount());
	}
	~RandomFunction(){}
	HRESULT init(void) { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int getFromInTo(int fromNum, int toNum) // inline�� ����, if���� ���� �ȵȴ�. ����ó�� �� �� ����.
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float GetFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

};