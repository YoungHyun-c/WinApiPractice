#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::Update(void)
{
	GameNode::update();
}

void MainGame::render(HDC hdc)
{
	HDC memDc = this->getBackBuffer()->getMemDC();

	PatBlt(memDc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	this->getBackBuffer()->render(hdc, 0, 0);
}