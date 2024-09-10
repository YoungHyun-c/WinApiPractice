#pragma once
#include "GameNode.h"

// ���� :
class MainGame : public GameNode
{
public:
	// constructer destructer
	MainGame() {};
	~MainGame() {};

	HRESULT init(void) override;
	void Render(HDC hdc) override;
	void Release(void) override;
	void Update(void) override;

private:
	RECT rc;
};

