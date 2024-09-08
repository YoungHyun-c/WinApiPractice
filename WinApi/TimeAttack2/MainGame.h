#pragma once

// Ό³Έν :
class MainGame
{
public:
	// constructer destructer
	MainGame();
	~MainGame();

	// delete Function
	MainGame(const MainGame& _Other) = delete;
	MainGame(MainGame&& _Other) noexcept = delete;
	MainGame& operator = (const MainGame& _Other) = delete;
	MainGame& operator = (MainGame&& _Other) noexcept = delete;

protected:

private:

};

