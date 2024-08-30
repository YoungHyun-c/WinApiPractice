#include <Windows.h>
#include <tchar.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include "stdafx.h"

#define CirCleSize 50

HINSTANCE _hInstance;
// �ڵ� : ������ â�� �ǹ��Ѵ�.
HWND _hwnd;
// ������ Ÿ��Ʋ
LPTSTR _lpszClass = TEXT("Windows API");
// TCHAR* pszString = _T("Windows API");

// �ݹ� �Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// wWinMain world wide�� ���������� �ٲٰڴ�.
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR    lpszCmdParam,
    int       nCmdShow)
{
    _hInstance = hInstance;

    // 1-1 ������â ����ü ���� �� �ʱ�ȭ
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0; // Ŭ������ ���� ���� �޸𸮸� �Ҵ� �Ҳ���. // Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; // ������ ``                             // ������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ������ �����Ѵ�.  // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                     // ���콺
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // ȭ�� ���� ���� �������� �ٸ� ������ �ҽ��� �ҷ��� ���ڴ�. // ������
    wndClass.hInstance = hInstance; // ������ �ν��Ͻ�                                   // ������ �ĺ��� ����.
    wndClass.lpfnWndProc = (WNDPROC)WndProc; // Long Pointer Function Numbering Window Pocedure  // ������ ���ν���
    wndClass.lpszClassName = _lpszClass; // ������ â �̸�.                              // Ŭ���� �̸�.
    wndClass.lpszMenuName = NULL; // ������ �޴� ����. (�ּ�ȭ, �ݱ�) // �޴��̸�.
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                           // ������ ��Ÿ��

    // 1-2 ������ Ŭ���� ���
    RegisterClass(&wndClass);

    // 1-3 ȭ�鿡 ������ ������ â ����.
    _hwnd = CreateWindow
    (
        _lpszClass,                 // ������ Ŭ���� �ĺ���
        _lpszClass,                 // ������ Ÿ��Ʋ �� �̸�
        WS_OVERLAPPEDWINDOW,        // ������ ��Ÿ��
        400,                        // ������ ȭ�� X ��ǥ
        100,                        // ������ ȭ�� Y ��ǥ
        800,                        // ������ ȭ�� ����ũ��.
        800,                        // ������ ȭ�� ����ũ��
        NULL,         // �θ� ������ -> NULL, GetDesktopWindow(), ������ â�� ������(����â, �����۰����â ��) �ʿ��ϸ� ����ϰ� �Ǵ� �뵵�̴�.
        (HMENU)NULL,                // �޴� �ڵ�
        hInstance,                  // �ν��Ͻ� ����
        NULL                        // �������� �ڽ� �����츦 �����ϸ� ���� / �ƴ϶�� NULL
    );

    ShowWindow(_hwnd, nCmdShow);

    MSG message;

    while (GetMessage(&message, 0, 0, 0))
    {

        TranslateMessage(&message);
        DispatchMessage(&message);
    }


    return (int)message.wParam;
}
class int2
{
public:
    inline int2()
    {
    }

    inline int2(int _X, int _Y) : X(_X), Y(_Y)
    {
    }

    int X = 0;
    int Y = 0;

public:
    inline int2 Half() const
    {
        return { X / 2, Y / 2 };
    }

    bool Check(const int2& _Other) const
    {
        return X == _Other.X && Y == _Other.Y;
    }

};

#define ColSize 50
bool CheckCollision(RECT _Me, RECT _other) {
    return (_Me.left < _other.right
        && _Me.right > _other.left
        && _Me.top < _other.bottom
        && _Me.bottom > _other.top);
}

bool IsScreenOver(const int2& _Pos)
{
    if (_Pos.X < 0)
    {
        return false;
    }
    if (_Pos.Y < 0)
    {
        return false;
    }
    if (_Pos.Y > 760)
    {
        return false;
    }
    if (_Pos.X > 790)
    {
        return false;
    }
    return true;
}

RECT RC;
RECT SmallRC;
RECT RC2;
HDC hdc;
RECT InitRCPos = { 400, 400, 100, 100 };
RECT InitRc2Pos = { 500, 500, 100, 100 };
int2 NextPos = {};
int2 RC2Pos = {};

void SwapRC(RECT& _Me, RECT& _Other)
{
    RECT MyRC;
    MyRC = _Me;
    _Me = _Other;
    _Other = MyRC;
}
#define CheckPos 25
void SmallRCSet(RECT& _SmallRc, RECT& _Other)
{
    _SmallRc.left = _Other.left + CheckPos;
    _SmallRc.top = _Other.top + CheckPos;
    _SmallRc.bottom = _Other.bottom - CheckPos;
    _SmallRc.right = _Other.right - CheckPos;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch (IMessage)
    {
    case WM_CREATE: // ������
        RC = RectMakeCenter(InitRCPos.left, InitRCPos.top, InitRCPos.right, InitRCPos.bottom);
        RC2 = RectMake(InitRc2Pos.left, InitRc2Pos.top, InitRc2Pos.right, InitRc2Pos.bottom);
        SmallRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y /2, InitRCPos.right / 2, InitRCPos.bottom / 2);
        break;
    case WM_PAINT: // �׸��±��
    {
        hdc = BeginPaint(hWnd, &ps);

        Rectangle(hdc, RC2.left, RC2.top, RC2.right, RC2.bottom);
        Rectangle(hdc, RC.left, RC.top, RC.right, RC.bottom);
        Rectangle(hdc, SmallRC.left, SmallRC.top, SmallRC.right, SmallRC.bottom);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);
        ReleaseDC(hWnd, hdc);
        break;
    case WM_RBUTTONDOWN:
        InvalidateRect(hWnd, &RC, TRUE);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            NextPos.X = RC.left;
            NextPos.X -= 10;
            if (IsScreenOver(NextPos) && !CheckCollision(RC, RC2))
            {
                RC.left -= 10;
                RC.right -= 10;
                if (SmallRC.right >= RC.right)
                {
                    SmallRC.left -= 10;
                    SmallRC.right -= 10;
                }
            }
            if (CheckCollision(RC, RC2) && IsScreenOver({ RC2.left, RC2.top }))
            {
                SwapRC(RC, RC2);
                SmallRCSet(SmallRC, RC);

                RC2.left -= 10;
                RC2.right -= 10;
                if (RC2.left <= 0)
                {
                    RC2.left = 0;
                    RC2.right= RC2.left + 100;
                }
                if (RC.left <= RC2.right)
                {
                    RC.left = RC2.right - 200;
                    RC.right = RC.left + 100;
                } 
            }
            break;
        case VK_RIGHT:
            NextPos.X = RC.right;
            NextPos.X += 10;
            if (IsScreenOver(NextPos) && !CheckCollision(RC, RC2))
            {
                RC.right += 10;
                RC.left += 10;
                if (SmallRC.left <= RC.left)
                {
                    SmallRC.left += 10;
                    SmallRC.right += 10;
                }
            }
            if (CheckCollision(RC, RC2) && IsScreenOver({ RC2.right, RC2.top }))
            {
                SwapRC(RC, RC2);
                SmallRCSet(SmallRC, RC);

                RC2.right += 10;
                RC2.left += 10;
                if (RC2.right >= 790)
                {
                    RC2.right = 790;
                    RC2.left = RC2.right - 100;
                }
                if (RC.right >= RC2.left)
                {
                    RC.right = RC2.left + 200;
                    RC.left = RC.right - 100;
                }
            }
            break;
        case VK_UP:
            NextPos.Y = RC.top;
            NextPos.Y -= 10;
            if (IsScreenOver(NextPos) && !CheckCollision(RC, RC2))
            {
                RC.top -= 10;
                RC.bottom -= 10;
                if (SmallRC.bottom >= RC.bottom)
                {
                    SmallRC.top -= 10;
                    SmallRC.bottom -= 10;
                }
            }
            if (CheckCollision(RC, RC2) && IsScreenOver({ RC2.left, RC2.top }))
            {
                SwapRC(RC, RC2);
                SmallRCSet(SmallRC, RC);

                RC2.top -= 10;
                RC2.bottom -= 10;
                if (RC2.top <= 0)
                {
                    RC2.top = 0;
                    RC2.bottom = RC2.top + 100;
                }
                if (RC.top <= RC2.bottom)
                {
                    RC.top = RC2.bottom - 200;
                    RC.bottom = RC.top + 100;
                }
            }
            break;
        case VK_DOWN:
            NextPos.Y = RC.bottom;
            NextPos.Y += 10;
            if (IsScreenOver(NextPos))
            {
                RC.bottom += 10;
                RC.top += 10;
                if (SmallRC.top <= RC.top)
                {
                    SmallRC.bottom += 10;
                    SmallRC.top += 10;
                }
            }
            if (CheckCollision(RC, RC2) && IsScreenOver({ RC2.left, RC2.bottom }))
            {
                SwapRC(RC, RC2);
                SmallRCSet(SmallRC, RC);

                RC2.bottom += 10;
                RC2.top += 10;
                if (RC2.bottom >= 760)
                {
                    RC2.bottom = 760;
                    RC2.top = RC2.bottom - 100;
                }
                if (RC.bottom >= RC2.top)
                {
                    RC.bottom = RC2.top + 200;
                    RC.top = RC.bottom - 100;
                }
            }
            break;
        case 'R':
        case 'r':
            RC = RectMakeCenter(InitRCPos.left, InitRCPos.top, InitRCPos.right, InitRCPos.bottom);
            RC2 = RectMake(InitRc2Pos.left, InitRc2Pos.top, InitRc2Pos.right, InitRc2Pos.bottom);
            SmallRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, InitRCPos.right / 2, InitRCPos.bottom / 2);
            break;
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }

        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return (DefWindowProc(hWnd, IMessage, wParam, lParam));
}


// 8 / 29
/*
 ���� 3.
 �簢�� ��ȥ �о� �ֱ�.

 -> ������ ū �簢�� 2���� ���� �簢�� 1��
 -> ���� ������ �� �ִ� �簢�� �ȿ��� ���� �簢���� �ִ�.
 -> �簢���� �����̸� ���� �簢�� ���� �����̰ų� / ū �簢���� ���� ���� �Ѵ�.
 �� �������� ���� ��õ.

 -> ����ó�� : ���� �簢���� ū �簢���� ��� �� ����.

 -> ū �簢������ �浹�� �Ǹ� ���� �簢���� �浹�� �� �ݴ��� �簢������ �̵��Ѵ�.
 �� �̶� ������ �� �ִ� �ֵ����� ���� �簢���� �����ϰ� �ִ� ū �簢��
 �� �𼭸��� ���� ����ó�� ������ ��. -> ���� �簢���� ū�簢���� ��������� �𼭸����� �ε������� �ȵ� �� ����.
*/