#pragma once
// RandomFunction
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		// API 공용 함수.
		// GetTickCount(): API 함수로 OS가 부팅된 후의 경과 시간을 체크.
		// 단위는 밀리 세컨 -> 밀리 세컨 단위이기 때문에 규모가 크지 않는 난수에 좋다.
		srand(GetTickCount());
	}
	~RandomFunction(){}
	HRESULT init(void) { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int getFromInTo(int fromNum, int toNum) // inline이 들어가면, if문이 들어가면 안된다. 예외처리 할 수 없음.
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