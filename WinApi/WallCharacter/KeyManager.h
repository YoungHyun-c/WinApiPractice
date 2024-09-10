#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

// Ό³Έν :
class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEY_MAX> _KeyDown;
	bitset<KEY_MAX> _KeyUp;

public:

	HRESULT init(void);
	bool isOnceKeyDown(int Key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyDown(void) { return _KeyDown; }
	bitset<KEY_MAX> getKeyUp(void) { return _KeyUp; }

	void setKeyDown(int key, bool state) { _KeyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _KeyUp.set(key, state); }

	KeyManager() {}
	~KeyManager() {}
};

