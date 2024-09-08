#pragma once

// Ό³Έν :
class GameNode
{
public:
	// constructer destructer
	GameNode();
	~GameNode();

	// delete Function
	GameNode(const GameNode& _Other) = delete;
	GameNode(GameNode&& _Other) noexcept = delete;
	GameNode& operator = (const GameNode& _Other) = delete;
	GameNode& operator = (GameNode&& _Other) noexcept = delete;

protected:

private:

};

