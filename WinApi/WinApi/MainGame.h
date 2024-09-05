#pragma once
#include "GameNode.h"

// ���� :
class MainGame : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	MainGame() {}
	~MainGame() {}

private:
	GImage* _bgImage;
	GImage* _plImage;

	RECT _rc;
	
	int _countA, _countB;
	int _alphaA, _alphaB;

	bool _isAlphaIncrease; // �� 4���� ������ �ϳ��� ��ĥ �� ����(�˾ƺ���)
};

