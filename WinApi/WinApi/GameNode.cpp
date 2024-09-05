#include "stdafx.h"
#include "GameNode.h"


HRESULT GameNode::init(void)
{
    SetTimer(_hWnd, 1, 10, NULL);
    KEYMANAGER->init();
    RND->init();
    this->setBackBuffer();
    return S_OK;
}

void GameNode::setBackBuffer(void)
{
    _backBuffer = new GImage;
    _backBuffer->init(WINSIZE_X, WINSIZE_Y);
}

void GameNode::release(void)
{
    KillTimer(_hWnd, 1);
    KEYMANAGER->releaseSingleton();
    RND->releaseSingleton();

    SAFE_DELETE(_backBuffer);
}

void GameNode::update(void)
{
    InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(HDC hdc)
{

}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        this->render(hdc);
        EndPaint(hWnd, &ps);
        break;
    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}