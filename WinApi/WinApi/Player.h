#pragma once
#include "GameNode.h"

enum class PlayerState
{
	Idle,
	Walk,
	Jump,
	Hang,
	GetUp,
	Max,
};

enum class PlayerDir
{
	Right,
	Left,
	Max,
};

// Ό³Έν :
class Player : public GameNode
{
public:
	// constructer destructer
	Player();
	~Player();

	HRESULT init() override;
	void update(void) override;
	void render(HDC hdc) override;

	void Gravity(RECT* _Ground, RECT* _AirGround, RECT* _Wall);

	void Hanging(RECT* _Ground);

protected:
	void ChangeState(PlayerState _State);
	void StateUpdate();

	void IdleStart();
	void IdleUpdate();

	void WalkStart();
	void WalkUpdate();

	void JumpStart();
	void JumpUpdate();

	void HangStart();
	void HangUpdate();

	void GetUpStart();
	void GetUpUpdate();


private:
	GImage _lionImage;
	GImage* _lionIdle;
	GImage* _lionWalk;
	GImage* _lionJump;
	GImage* _lionHang;
	GImage* _lionGetUp;

	PlayerDir Dir = PlayerDir::Right;
	bool _isLeft = false;
	int _count;
	int _index;
	float X;
	float Y;

	PlayerState State = PlayerState::Idle;

private:
	void GravityReset()
	{
		GravityVector = 0.0f;
	}
	void GravityOff()
	{
		IsGravity = false;
	}
	void SetGravityVector(float _GravityVector)
	{
		GravityVector = _GravityVector;
	}

	float GravityPower = 10.0f;
	float GravityVector = 0.0f;

	bool IsGravity = true;
	bool IsJump = false;
	bool Hang = false;

	RECT DownCheck;
	RECT RightCheck;
	RECT LeftCheck;
};

