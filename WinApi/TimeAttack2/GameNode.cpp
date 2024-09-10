#include "stdafx.h"
#include "GameNode.h"


HRESULT GameNode::init(void)
{
	SetTimer(_hWnd, 1, 10, NULL);
	KEYMANAGER->init();

	return S_OK;
}

void GameNode::Render(HDC hdc)
{

}

void GameNode::Update(void)
{
	InvalidateRect(_hWnd, NULL, true);
}

void GameNode::Release(void)
{
	KillTimer(_hWnd, 1);

	KEYMANAGER->releaseSingleton();
	RND->releaseSingleton();
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static POINT pt = { 0, 0 };

	switch (iMessage)
	{
	case WM_TIMER:
		this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->Render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}