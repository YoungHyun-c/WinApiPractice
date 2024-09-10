#include "stdafx.h"
#include "Player.h"

void Player::IdleStart()
{
	_lionIdle->setX(X);
	_lionIdle->setY(Y);
	_lionImage = *_lionIdle;
	IsGravity = true;
}
void Player::IdleUpdate()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		ChangeState(PlayerState::Walk);
		return;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && !IsJump)
	{
		ChangeState(PlayerState::Jump);
		return;
	}
}
void Player::WalkStart()
{
	_lionWalk->setX(X);
	_lionWalk->setY(Y);
	_lionImage = *_lionWalk;
	IsGravity = true;
}
void Player::WalkUpdate()
{
	IsGravity = true;
	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && !IsJump)
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		DownCheck.left -= 8.0f;
		DownCheck.right -= 8.0f;
		LeftCheck.left -= 8.0f;
		LeftCheck.right -= 8.0f;
		RightCheck.left -= 8.0f;
		RightCheck.right -= 8.0f;
		_lionImage.setX(X - 8.0f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		DownCheck.left += 8.0f;
		DownCheck.right += 8.0f;
		LeftCheck.left += 8.0f;
		LeftCheck.right += 8.0f;
		RightCheck.left += 8.0f;
		RightCheck.right += 8.0f;
		_lionImage.setX(X + 8.0f);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::JumpStart()
{
	_lionJump->setX(X);
	_lionJump->setY(Y - 250.0f);
	_lionImage = *_lionJump;
	IsGravity = true;
	IsJump = true;

	SetGravityVector(-1.0f * 250.0f);
	DownCheck.top -= 250.0f;
	DownCheck.bottom -= 250.0f;
	LeftCheck.top -= 250.0f;
	LeftCheck.bottom -= 250.0f;
	RightCheck.top -= 250.0f;
	RightCheck.bottom -= 250.0f;
}
void Player::JumpUpdate()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		DownCheck.left -= 8.0f;
		DownCheck.right -= 8.0f;
		LeftCheck.left -= 8.0f;
		LeftCheck.right -= 8.0f;
		RightCheck.left -= 8.0f;
		RightCheck.right -= 8.0f;
		_lionImage.setX(X - 8.0f);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		DownCheck.left += 8.0f;
		DownCheck.right += 8.0f;
		LeftCheck.left += 8.0f;
		LeftCheck.right += 8.0f;
		RightCheck.left += 8.0f;
		RightCheck.right += 8.0f;
		_lionImage.setX(X + 8.0f);
	}

	if (!IsGravity)
	{
		IsJump = false;
		IsGravity = false;
		GravityReset();
		ChangeState(PlayerState::Idle);
		return;
	}
}
void Player::HangStart()
{
	Hang = true;
	_lionHang->setX(X);
	_lionHang->setY(Y);
	_lionImage = *_lionHang;
}
void Player::HangUpdate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		ChangeState(PlayerState::GetUp);
		return;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		Hang = false;
		ChangeState(PlayerState::Idle);
		return;
	}
}
#define HangX 80.0f
#define HangY 200.0f
void Player::GetUpStart()
{
	Hang = false;
	DownCheck.top -= HangY;
	DownCheck.bottom -= HangY;
	LeftCheck.top -= HangY;
	LeftCheck.bottom -= HangY;
	RightCheck.top -= HangY;
	RightCheck.bottom -= HangY;

	DownCheck.left += HangX;
	DownCheck.right += HangX;
	LeftCheck.left += HangX;
	LeftCheck.right += HangX;
	RightCheck.left += HangX;
	RightCheck.right += HangX;

	_lionGetUp->setX(X + HangX);
	_lionGetUp->setY(Y - HangY);
	_lionImage = *_lionGetUp;
}
void Player::GetUpUpdate()
{
	if (_index = _lionImage.getMaxFrameX())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}