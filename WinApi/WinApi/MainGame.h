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
	GImage* _GroundImage;
	GImage* _AirGroundImage;
	GImage* _WallImage;

	RECT Ground;
	RECT AirGround;
	RECT HangGround;
	RECT Wall;

	GImage _lionImage;
	GImage* _lionIdle;
	GImage* _lionWalk;
	GImage* _lionJump;
	GImage* _lionHang;
	GImage* _lionGetUp;
	class Player* pPlayer;

	GImage* _plImage;
	RECT _GroundRc;
	
	int _countA, _countB;
	int _alphaA, _alphaB;

	bool _isAlphaIncrease; // 위 4개의 변수를 하나로 통칠 수 있음(알아보기)


	bool _isLeft = false;
	int _count;
	int _index;
};

