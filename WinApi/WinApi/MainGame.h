#pragma once
#include "GameNode.h"

// 설명 :
class MainGame : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	MainGame() {}
	~MainGame() {}

private:
	GImage* _bgImage;
	GImage* _plImage;

	RECT _rc;
	
	int _countA, _countB;
	int _alphaA, _alphaB;

	bool _isAlphaIncrease; // 위 4개의 변수를 하나로 통칠 수 있음(알아보기)
};

