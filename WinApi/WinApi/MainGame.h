#pragma once
#include "GameNode.h"

// Ό³Έν :
class MainGame : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void Update(void);
	void render(HDC hdc);

	MainGame() {}
	~MainGame() {}
};

