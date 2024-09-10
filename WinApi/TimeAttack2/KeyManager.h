#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase<KeyManager>
{
public:
	// constructer destructer
	KeyManager() {};
	~KeyManager() {};

	HRESULT init(void);
	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	void setDownKey(int key, bool state) { _DownKey.set(key, state); }
	void setUpKey(int key, bool state) { _UpKey.set(key, state); }

	std::bitset<KEY_MAX> GetDownKey() { return _DownKey; }
	std::bitset<KEY_MAX> GetUpKey() { return _UpKey; }


private:
	std::bitset<KEY_MAX> _DownKey;
	std::bitset<KEY_MAX> _UpKey;

};
