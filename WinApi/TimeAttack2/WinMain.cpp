#include "stdafx.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    _hInstance = hInstance;
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.lpfnWndProc = (WNDPROC)WndProc;
    wndClass.lpszClassName = WINNAME;
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);

    _hWnd = CreateWindow(
        WINNAME, WINNAME, WINSTYLE,
        WINSTART_X, WINSTART_Y,
        WINSIZE_X, WINSIZE_X,
        NULL, NULL, hInstance, NULL);

    SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);


    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}


void SetWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };
    AdjustWindowRect(&rc, WINSTYLE, false);

    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}
