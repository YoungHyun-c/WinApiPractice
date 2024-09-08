#pragma once

// Ό³Έν :
class KeyManager
{
public:
	// constructer destructer
	KeyManager();
	~KeyManager();

	// delete Function
	KeyManager(const KeyManager& _Other) = delete;
	KeyManager(KeyManager&& _Other) noexcept = delete;
	KeyManager& operator = (const KeyManager& _Other) = delete;
	KeyManager& operator = (KeyManager&& _Other) noexcept = delete;

protected:

private:

};

