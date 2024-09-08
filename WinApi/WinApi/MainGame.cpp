#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"


HRESULT MainGame::init(void)
{
	GameNode::init();

	_bgImage = new GImage;
	_bgImage->init("Resources/Images/BackGround/MyBackGround.bmp", WINSIZE_X, WINSIZE_Y);

	_GroundImage = new GImage;
	_GroundImage->init("Resources/Images/Object/Wall.bmp", 1024, 300, false);
	Ground = RectMake(0, 500, 1024, 300);

	_AirGroundImage = new GImage;
	_AirGroundImage->init("Resources/Images/Object/Ground.bmp", 300, 150, true, RGB(255, 0, 255));
	AirGround = RectMake(100, 300, 300, 75);

	_WallImage = new GImage;
	_WallImage->init("Resources/Images/Object/Wall.bmp", 300, 200, false);
	Wall = RectMake(800, 300, 300, 200);

	HangGround = RectMake(800, 300, 50, 50);

	{
		pPlayer = new Player();
		pPlayer->init();
	}

	_countA = _countB = 255;
	_alphaA = _alphaB = 255;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_plImage);

	SAFE_DELETE(pPlayer);
}

void MainGame::update(void)
{
	GameNode::update();

	pPlayer->update();
	pPlayer->Gravity(&Ground, &AirGround, &Wall);
	
	pPlayer->Hanging(&HangGround);
}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getBackBuffer()->getMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(memDC, Ground.left, Ground.top, Ground.right, Ground.bottom);
		Rectangle(memDC, AirGround.left, AirGround.top, AirGround.right, AirGround.bottom);
		Rectangle(memDC, Wall.left, Wall.top, Wall.right, Wall.bottom);
		//Rectangle(memDC, HangGround.left, HangGround.top, HangGround.right, HangGround.bottom);
	}
	else
	{
		_bgImage->AlphaRender(memDC, _alphaA);
		_GroundImage->render(memDC, 0, 500);
		_AirGroundImage->render(memDC, 100, 300);
		_WallImage->render(memDC, 800, 300);
	}

	pPlayer->render(memDC);

	//_plImage->frameRender(hdc, 100, 100);

	//_bgImage->render(memDC, _rc.left, _rc.top, 500, 300, 300, 300); // Å¬¸®ÇÎ

	this->getBackBuffer()->render(hdc, 0, 0);
}