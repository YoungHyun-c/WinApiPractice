#include "stdafx.h"
#include "MainGame.h"

#define AniFrame 4
#define PlayerSize 3

HRESULT MainGame::init(void)
{
	GameNode::init();

	_bgImage = new GImage;
	_bgImage->init("Resources/Images/BackGround/MyBackGround.bmp", WINSIZE_X, WINSIZE_Y);

	_GroundImage = new GImage;
	_GroundImage->init("Resources/Images/Object/Wall.bmp", 1024, 300, false);
	_AirGroundImage = new GImage;
	_AirGroundImage->init("Resources/Images/Object/Ground.bmp", 300, 150, true, RGB(255, 0, 255));

	_WallImage = new GImage;
	_WallImage->init("Resources/Images/Object/Wall.bmp", 300, 200, false);

	{
		_lionIdle = new GImage;
		_lionIdle->init("Resources/Images/Object/Idle.bmp", WINSIZE_X / 2, WINSIZE_Y / 2, 150 * PlayerSize, 70 * PlayerSize, 5, 2, true, RGB(255, 0, 255));

		_lionWalk = new GImage;
		_lionWalk->init("Resources/Images/Object/Walking.bmp", WINSIZE_X / 2, WINSIZE_Y / 2, 259 * PlayerSize, 68 * PlayerSize, 7, 2, true, RGB(255, 0, 255));

		_lionImage;
		_lionImage = *_lionIdle;
	}

	_count = _index = 0;

	_PlayerRc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 30 * PlayerSize, 35 * PlayerSize);

	_countA = _countB = 255;
	_alphaA = _alphaB = 255;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_plImage);

	SAFE_DELETE(_lionIdle);
	SAFE_DELETE(_lionWalk);
}

void MainGame::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_PlayerRc.top -= 3;
		_PlayerRc.bottom -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_PlayerRc.left -= 3;
		_PlayerRc.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_PlayerRc.left += 3;
		_PlayerRc.right += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_PlayerRc.top += 3;
		_PlayerRc.bottom += 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_lionImage = *_lionWalk;
		_lionImage.setX(_lionImage.getX() - 8.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_lionImage = *_lionWalk;
		_lionImage.setX(_lionImage.getX() + 8.0f);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		float X = _lionImage.getX();
		_lionIdle->setX(X);
		_lionImage = *_lionIdle;
	}


	if (_isLeft)
	{
		_count++;
		_lionImage.setCurrentFrameY(1);
		if (_count % AniFrame == 0)
		{
			_index--;
			if (_index < 0)
			{
				_index = 7;
			}
			_lionImage.setCurrentFrameX(_index);
		}
	}
	else
	{
		_count++;

		_lionImage.setCurrentFrameY(0);
		if (_count % AniFrame == 0)
		{
			_index++;
			if (_index > 7)
			{
				_index = 0;
			}
			_lionImage.setCurrentFrameX(_index);
		}
	}
}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getBackBuffer()->getMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_bgImage->AlphaRender(memDC, _alphaA);

	_GroundImage->render(memDC, 0, 500);
	_WallImage->render(memDC, 800, 300);
	_AirGroundImage->render(memDC, 100, 300);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(memDC, _PlayerRc.left, _PlayerRc.top, _PlayerRc.right, _PlayerRc.bottom);
	}

	/*_plImage->AlphaRender(memDC, _rc.left, _rc.top, _alphaB);*/


	_lionImage.frameRender(memDC, _lionImage.getX(), _lionImage.getY());

	//_plImage->frameRender(hdc, 100, 100);

	//_bgImage->render(memDC, _rc.left, _rc.top, 500, 300, 300, 300); // Å¬¸®ÇÎ

	this->getBackBuffer()->render(hdc, 0, 0);
}