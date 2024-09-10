#pragma once

// Ό³Έν :
class GameNode abstract
{
public:
	// constructer destructer
	GameNode() {};
	virtual ~GameNode() {};

	virtual HRESULT init(void);
	virtual void Render(HDC hdc);
	virtual void Update(void);
	virtual void Release(void);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:

};

