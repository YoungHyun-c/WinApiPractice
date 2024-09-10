#pragma once
#include "GImage.h"

class GameNode
{
private:
	GImage* _backBuffer;
	void setBackBuffer(void);

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GImage* getBackBuffer() { return _backBuffer; }

	GameNode() : _backBuffer(nullptr) {}
	virtual ~GameNode() {}
};