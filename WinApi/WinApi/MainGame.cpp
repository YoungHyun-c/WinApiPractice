#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_bgImage = new GImage;
	_bgImage->init("Resources/Images/BackGround/backGround.bmp", WINSIZE_X, WINSIZE_Y);

	_plImage = new GImage;
	_plImage->init("Resources/Images/Object/character.bmp", 95, 117, true, RGB(255, 0, 255));

	_rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 200, 88, 117);

	_countA = _countB = 0;
	_alphaA = _alphaB = 0;

	_isAlphaIncrease = false;
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_plImage);
}

void MainGame::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_rc.top -= 3;
		_rc.bottom -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_rc.left -= 3;
		_rc.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_rc.left += 3;
		_rc.right += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_rc.top += 3;
		_rc.bottom += 3;
	}

	_countA++;
	if (_countA % 3 == 0)
	{
		_alphaA++;
		if (_alphaA >= 265) _alphaA = 0;
	}

	_countB++;
	if (_countB % 3 == 0)
	{
		_alphaB += 5;
		if (_alphaB >= 265) _alphaB = 0;
	}
}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getBackBuffer()->getMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_bgImage->AlphaRender(memDC, _alphaA);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(memDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

	_plImage->AlphaRender(memDC, _rc.left, _rc.top, _alphaB);

	//_bgImage->render(memDC, _rc.left, _rc.top, 500, 300, 300, 300); // Å¬¸®ÇÎ

	this->getBackBuffer()->render(hdc, 0, 0);
}