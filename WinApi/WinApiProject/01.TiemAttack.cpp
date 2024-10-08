#include <Windows.h>
#include <tchar.h>

HWND _hWnd;
HINSTANCE _hInstance;
LPTSTR _lpszClass = TEXT("WInAPi Class");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPreveInstance,
    LPSTR   lpszCmdParam,
    int nCmdShow)
{
    _hInstance = hInstance;

    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(_hInstance, IDC_ARROW);
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wndClass.hInstance = _hInstance;
    wndClass.lpfnWndProc = (WNDPROC)WndProc;
    wndClass.lpszClassName = _lpszClass;
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        _lpszClass,
        _lpszClass,
        WS_OVERLAPPEDWINDOW,
        400,
        100,
        800,
        800,
        NULL,
        (HMENU)NULL,
        _hInstance,
        NULL
    );

    ShowWindow(_hWnd, nCmdShow);

    MSG Message;

    while (GetMessage(&Message, 0, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessageW(&Message);
    }

    return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    switch (IMessage)
    {
    case WM_CREATE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return (DefWindowProc(hwnd, IMessage, wParam, lParam));
}