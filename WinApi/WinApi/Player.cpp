#include "stdafx.h"
#include "Player.h"

#define AniFrame 4
#define PlayerSize 3

Player::Player()
{
}

Player::~Player()
{

}

HRESULT Player::init()
{
	{
		_lionIdle = new GImage;
		_lionIdle->init("Resources/Images/Object/Idle.bmp", WINSIZE_X / 2, WINSIZE_Y / 2, 150 * PlayerSize, 70 * PlayerSize, 5, 2, true, RGB(255, 0, 255));

		_lionWalk = new GImage;
		_lionWalk->init("Resources/Images/Object/Walking.bmp", WINSIZE_X / 2, WINSIZE_Y / 2, 259 * PlayerSize, 68 * PlayerSize, 7, 2, true, RGB(255, 0, 255));

		_lionJump = new GImage;
		_lionJump->init("Resources/Images/Object/Jump.bmp", WINSIZE_X / 2, WINSIZE_Y / 2, 190 * PlayerSize, 74 * PlayerSize, 5, 2, true, RGB(255, 0, 255));

		_lionHang = new GImage;
		_lionHang->init("Resources/Images/Object/Hanging.bmp", WINSIZE_X / 2, WINSIZE_Y / 2, 72 * PlayerSize, 100 * PlayerSize, 2, 2, true, RGB(255, 0, 255));

		_lionGetUp = new GImage;
		_lionGetUp->init("Resources/Images/Object/GetUp.bmp", WINSIZE_X / 2, WINSIZE_Y / 2, 90 * PlayerSize, 120 * PlayerSize, 3, 2, true, RGB(255, 0, 255));

		_lionImage = *_lionIdle;
	}

	// Collision
	{
		DownCheck = RectMake(_lionImage.getX() + _lionImage.getFrameWidth()/2, (_lionImage.getY() - 10.0f + _lionImage.getHeight()/2), 10, 10);

		RightCheck = RectMake(_lionImage.getX() + _lionImage.getFrameWidth() + 5.0f, (_lionImage.getY() - 10.0f), 20, 20);
		LeftCheck = RectMake(_lionImage.getX() - 5.0f, (_lionImage.getY() - 10.0f), 20, 20);
	}
	_count = _index = 0;

	return S_OK;
}

void Player::update(void)
{
	X = _lionImage.getX();
	Y = _lionImage.getY();
	
	StateUpdate();

	if (_isLeft)
	{
		_count++;
		_lionImage.setCurrentFrameY(1); 
		if (_count % AniFrame == 0)
		{
			_index--;
			if (_index < 0)
			{
				_index = _lionImage.getMaxFrameX();
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
			if (_index > _lionImage.getMaxFrameX())
			{
				_index = 0;
			}
			_lionImage.setCurrentFrameX(_index);
		}
	}
}

void Player::StateUpdate()
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate();
	case PlayerState::Walk:
		return WalkUpdate();
	case PlayerState::Jump:
		return JumpUpdate();
	case PlayerState::Hang:
		return HangUpdate();
	case PlayerState::GetUp:
		return GetUpUpdate();
	default:
		break;
	}
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Walk:
			WalkStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Hang:
			HangStart();
			break;
		case PlayerState::GetUp:
			GetUpStart();
			break;
		case PlayerState::Max:
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Player::render(HDC hdc)
{
	_lionImage.frameRender(hdc, _lionImage.getX(), _lionImage.getY());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, DownCheck.left, DownCheck.top, DownCheck.right, DownCheck.bottom);
		Rectangle(hdc, RightCheck.left, RightCheck.top, RightCheck.right, RightCheck.bottom);
		Rectangle(hdc, LeftCheck.left, LeftCheck.top, LeftCheck.right, LeftCheck.bottom);
	}
}

void Player::Gravity(RECT* _Ground, RECT* _AirGround, RECT* _Wall)
{
	if (false == IsGravity || Hang == true)
	{
		return;
	}

	RECT CHECK;
	if (IntersectRect(&CHECK, &DownCheck, _Ground) || IntersectRect(&CHECK, &DownCheck, _AirGround) || IntersectRect(&CHECK, &DownCheck, _Wall))
	{
		IsGravity = false;
		IsJump = false;
		GravityReset();
	}
	else
	{
		GravityVector += GravityPower;
		DownCheck.bottom += GravityPower;
		DownCheck.top += GravityPower;

		LeftCheck.bottom += GravityPower;
		LeftCheck.top += GravityPower;

		RightCheck.top += GravityPower;
		RightCheck.bottom += GravityPower;
		_lionImage.setY(DownCheck.top - _lionImage.getFrameHeight());
	}
}

void Player::Hanging(RECT* _Ground)
{
	RECT CHECK;
	if (IntersectRect(&CHECK, &RightCheck, _Ground) || IntersectRect(&CHECK, &LeftCheck, _Ground))
	{
		ChangeState(PlayerState::Hang);
		return;
	}
}