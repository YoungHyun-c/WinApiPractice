// WinApiTest.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#include "stdafx.h"
//#include <windowsx.h> // ���� ƥ�� ����Ѵ�.
#include "MainGame.h"

HINSTANCE _hInstance;
// �ڵ� : ������ â�� �ǹ��Ѵ�.
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
MainGame* _mg;

// �Լ�
// �ݹ� �Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);

// wWinMain world wide�� ���������� �ٲٰڴ�.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    _mg = new MainGame();
    _hInstance = hInstance;

    /*
    winMain�� ����
    �� 1. ������ â�� ���� �� ȭ�鿡 ����.
        -> ȭ�鿡 â�� ���� ���ؼ��� 4���� ó���� ����Ǿ�� �Ѵ�.
    �� 2. �޼��� ����
    */

    // 1-1 ������â ����ü ���� �� �ʱ�ȭ
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0; // Ŭ������ ���� ���� �޸𸮸� �Ҵ� �Ҳ���. // Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; // ������ ``                             // ������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ������ �����Ѵ�.  // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                     // ���콺
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // ȭ�� ���� ���� �������� �ٸ� ������ �ҽ��� �ҷ��� ���ڴ�. // ������
    wndClass.hInstance = hInstance; // ������ �ν��Ͻ�                                   // ������ �ĺ��� ����.
    wndClass.lpfnWndProc = (WNDPROC)WndProc; // Long Pointer Function Numbering Window Pocedure  // ������ ���ν���
    wndClass.lpszClassName = WINNAME; // ������ â �̸�.                              // Ŭ���� �̸�.
    wndClass.lpszMenuName = NULL; // ������ �޴� ����. (�ּ�ȭ, �ݱ�) // �޴��̸�.
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                           // ������ ��Ÿ��

    // 1-2 ������ Ŭ���� ���
    RegisterClass(&wndClass);

    // 1-3 ȭ�鿡 ������ ������ â ����.
    _hWnd = CreateWindow
    (
        WINNAME,                 // ������ Ŭ���� �ĺ���
        WINNAME,                 // ������ Ÿ��Ʋ �� �̸�
        WINSTYLE,        // ������ ��Ÿ��
        WINSTART_X,                        // ������ ȭ�� X ��ǥ
        WINSTART_Y,                        // ������ ȭ�� Y ��ǥ
        WINSIZE_X,                        // ������ ȭ�� ����ũ��.
        WINSIZE_Y,                        // ������ ȭ�� ����ũ��
        NULL,         // �θ� ������ -> NULL, GetDesktopWindow(), ������ â�� ������(����â, �����۰����â ��) �ʿ��ϸ� ����ϰ� �Ǵ� �뵵�̴�.
        (HMENU)NULL,                // �޴� �ڵ�
        hInstance,                  // �ν��Ͻ� ����
        NULL                        // �������� �ڽ� �����츦 �����ϸ� ���� / �ƴ϶�� NULL
    );

    SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
    // 1-4 ȭ�鿡 ������â �����ֱ�
    ShowWindow(_hWnd, nCmdShow);

    if (FAILED(_mg->init()))
    {
        return 0;
    }

    MSG message;

    while (GetMessage(&message, 0, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    _mg->release();
    UnregisterClass(WINNAME, hInstance);

    return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

// ������ ����ȭ�� ���ؼ� ���Ǵ� Z ����.
void SetWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    // ���� ������ ũ�� ����.
    // AdjustWindowRect() : RECT ����ü, �� ��Ÿ��, �޴�����
    AdjustWindowRect(&rc, WINSTYLE, false);

    // ��Ʈ�� ������ ������ ������ ����.
    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

}
