#pragma once
#include "GameNode.h"

// ���� :
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

	bool _isAlphaIncrease; // �� 4���� ������ �ϳ��� ��ĥ �� ����(�˾ƺ���)


	bool _isLeft = false;
	int _count;
	int _index;
};

