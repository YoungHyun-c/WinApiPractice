#include "stdafx.h"
#include "KeyManager.h"


HRESULT KeyManager::init(void)
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setDownKey(i, false);
		this->setUpKey(i, false);
	}
	return S_OK;
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) && 0x8000)
	{
		if (this->GetDownKey()[key])
		{
			setDownKey(key, true);
			return true;
		}
	}
	else
	{
		setDownKey(key, false);
	}
	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) && 0x8000)
	{
		setUpKey(key, true);
	}
	else
	{
		if (this->GetUpKey()[key])
		{
			setUpKey(key, false);
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) && 0x8000) return true;

	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) && 0x0001) return true;

	return false;
}