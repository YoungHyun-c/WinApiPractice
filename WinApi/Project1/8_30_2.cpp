// WinApiTest.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#include "stdafx.h"
#include <windowsx.h> // ���� ƥ�� ����Ѵ�.

HINSTANCE _hInstance;
// �ڵ� : ������ â�� �ǹ��Ѵ�.
HWND _hwnd;
POINT _ptMouse = { 0, 0 };

// �Լ�
// �ݹ� �Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);

RECT rc;
RECT _rc1, _rc2;

int centerX;
int centerY;

// wWinMain world wide�� ���������� �ٲٰڴ�.
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR    lpszCmdParam,
    int       nCmdShow)
{
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
    _hwnd = CreateWindow
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
    ShowWindow(_hwnd, nCmdShow);

    MSG message;


    while (GetMessage(&message, 0, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;

    PAINTSTRUCT ps;

    static POINT pt = { 0, 0 };
    char strPT[128] = "";

    char str[] = "������";

    switch (IMessage)
    {
    case WM_CREATE: // ������
        rc = RectMakeCenter(400, 400, 100, 100);
        _rc1 = RectMakeCenter(WINSIZE_X / 2 + 200, WINSIZE_Y / 2, 100, 100);
        _rc1 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

        centerX = WINSIZE_X / 2;
        centerY = WINSIZE_Y / 2;

        break;

    case WM_PAINT: // �׸��±��
    {
        hdc = BeginPaint(hWnd, &ps);

        wsprintf(strPT, "X : %d      Y : %d", pt.x, pt.y); // ���ڸ� ���ڿ��� ����Ҷ� ����.
        TextOut(hdc, 10, 10, strPT, strlen(strPT));

        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
        DrawRectMake(hdc, rc);

        MakeCoordi(hdc, WINSIZE_X, WINSIZE_Y);

        Rectangle(hdc, _rc1.left, _rc1.top, _rc1.right, _rc1.bottom);
        Rectangle(hdc, _rc2.left, _rc2.top, _rc2.right, _rc2.bottom);

        EllipseMakeCenter(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

        Rectangle(hdc, centerX, centerY, 100, 100);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_MOUSEMOVE:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        // pt.x = GET_X_LPARAM(lParam);

        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_LBUTTONDOWN:
        centerX = RND->getInt(WINSIZE_X);
        centerY = RND->getInt(WINSIZE_Y);

        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_RBUTTONDOWN:

        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            break;
        case VK_RIGHT:
            break;
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    case WM_DESTROY:
        // PostQuitMessage : �� �Լ��� �޼��� ť�� QUIT �޼����� ������ ������ ����.
        // Quit �޼����� �����ϴ� ���� GetMessage�� FALSE�� ��ȯ�ϹǷ� �޼��� ������ ����ȴ�.
        PostQuitMessage(0);
        break;
    }

    return (DefWindowProc(hWnd, IMessage, wParam, lParam));
}

// ������ ����ȭ�� ���ؼ� ���Ǵ� Z ����.
void SetWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    // ���� ������ ũ�� ����.
    // AdjustWindowRect() : RECT ����ü, �� ��Ÿ��, �޴�����
    AdjustWindowRect(&rc, WINSTYLE, false);

    // ��Ʈ�� ������ ������ ������ ����.
    SetWindowPos(_hwnd, NULL,
        x, y,
        (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

}
