#include <Windows.h>
#include <tchar.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include "CommonMacroFunction.h"

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

void MyCircle(HDC _hdc, int _X, int _Y, int _R)
{
    int R = _R;
    for (int i = 0; i < 361; i++)
    {
        MoveToEx(_hdc, _X + static_cast<int>(cos(i) * R), _Y + static_cast<int>(sin(i) * R), NULL);
        LineTo(_hdc, _X + 1 + static_cast<int>(cos(i) * R), _Y + 1 + static_cast<int>(sin(i) * R));
    }
}

void MyUpHalfCircle(HDC _hdc, int _X, int _Y, int _R)
{
    int R = _R;
    for (int i = 0; i < 361; i++)
    {
        MoveToEx(_hdc, _X + static_cast<int>(cos(i) * R), _Y - abs(static_cast<int>(sin(i) * R)), NULL);
        LineTo(_hdc, _X + 1 + static_cast<int>(cos(i) * R), _Y + 1 - abs(static_cast<int>(sin(i) * R)));
    }
}

void MyDownHalfCircle(HDC _hdc, int _X, int _Y, int _R)
{
    int R = _R;
    for (int i = 0; i < 361; i++)
    {
        MoveToEx(_hdc, _X + static_cast<int>(cos(i) * R), _Y + abs(static_cast<int>(sin(i) * R)), NULL);
        LineTo(_hdc, _X + 1 + static_cast<int>(cos(i) * R), _Y + 1 + abs(static_cast<int>(sin(i) * R)));
    }
}

void MyAngle(HDC _hdc, int _X, int _Y, int _R, int _Angle)
{
    double PI = 3.14;
    for (float i = 0; i < _Angle; i++)
    {
        double radian = i * (PI / 180.0);
        int x = _X + static_cast<int>(_R * cos(radian));
        int y = _Y - static_cast<int>(_R * sin(radian));
        MoveToEx(_hdc, x, y, NULL);
        LineTo(_hdc, x + 1, y + 1);
    }
}


typedef struct { float x, y; } Point2D;

//Point2D PointOnCubicBezier(HDC hdc, Point2D* cp, float t)
//{
//    float ax, bx, cx, ay, by, cy, tSquared, tCubed;
//    Point2D result;
//
//    // ���׽� ����� ����Ѵ�.
//    cx = 3.0 * (cp[1].x - cp[0].x);
//    bx = 3.0 * (cp[2].x - cp[1].x) - cx;
//    ax = cp[3].x - cp[0].x - cx - bx;
//
//    cy = 3.0 * (cp[1].y - cp[0].y);
//    by = 3.0 * (cp[2].y - cp[1].y) - cy;
//    ay = cp[3].y - cp[0].y - cy - by;
//
//    tSquared = t * t;
//    tCubed = tSquared * t;
//
//    result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + cp[0].x;
//    result.y = (ay * tCubed) + (bx * tSquared) + (cy * t) + cp[0].y;
//
//    MoveToEx(hdc, result.x, result.y, NULL);
//    LineTo(hdc, result.x + 2, result.y + 2);
//    return result;
//}
//
//void Computerbezier(HDC hdc, Point2D* cp, int NumberOfPoints, Point2D* Curve)
//{
//    float dt;
//    int i;
//
//    dt = 1.0 / (NumberOfPoints - 1);
//
//    for (i = 0; i < NumberOfPoints; i++)
//        Curve[i] = PointOnCubicBezier(hdc, cp, i * dt);
//}

Point2D* Pos1 = new Point2D({ 300, 300 });
Point2D* Pos2 = new Point2D({ 400, 400 });

void PrintCircle(HDC hdc, float _X, float _Y, float _R, float _Rate = 40.0f)
{
    float Rpow = pow(_R, 2);

    for (float X = _X - _R ; X < _X + _R; X++)
    {
        for (float Y = _Y - _R; Y < _Y + _R; Y++)
        {
            float Xpow = (_X - X) * (_X - X);
            float Ypow = (_Y - Y) * (_Y - Y);
            if (Xpow + Ypow - Rpow < _Rate && Xpow + Ypow - Rpow >= - (_Rate * _Rate))
            {
                SetPixel(hdc, X, Y, RGB(255, 0, 0));
            }
        }
    }
}

void PrintStarCircle(HDC hdc, float _X, float _Y, float _R, float _Rate = 40.0f)
{
    float Rpow = pow(_R, 2);

    for (float X = _X - _R; X < _X + _R; X++)
    {
        for (float Y = _Y - _R; Y < _Y + _R; Y++)
        {
            float Xpow = (_X - X) * (_X - X);
            float Ypow = (_Y - Y) * (_Y - Y);
            if (Xpow + Ypow - Rpow < _Rate && Xpow + Ypow - Rpow >= -(_Rate * _Rate))
            {
                SetPixel(hdc, X, Y, RGB(255, 0, 0));
            }

            if (Y == 240 && Xpow + Ypow < Rpow)
            {
                SetPixel(hdc, X, Y, RGB(255, 0, 0));
            }
            else if (Y - 90 == X && Xpow + Ypow < Rpow)
            {
                SetPixel(hdc, X, Y, RGB(255, 0, 0));
            }
            else if ((_Y + _R) == (X - 190 + Y) && Xpow + Ypow < Rpow)
            {
                SetPixel(hdc, X, Y, RGB(255, 0, 0));
            }
            else if ((_Y + _R) == (X + 250 + ((Y + 20) / 3)) && Xpow + Ypow < Rpow)
            {
                SetPixel(hdc, X, Y, RGB(255, 0, 0));
            }
            else if (Y/3 + 260 == X - 100  && Xpow + Ypow < Rpow)
            {
                SetPixel(hdc, X, Y, RGB(255, 0, 0));
            }
        }
    }
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    static int Num = 0;
    static int Dan = 2;

    const int X = 150;
    const int Y = 10;

    char Ch[256];
    RECT rc = { 0 + (250 * Num), 0, (250 + (300 * Num)), 400 };


    switch (IMessage)
    {
    case WM_CREATE: // ������
        break;
    case WM_PAINT: // �׸��±��
    {
        hdc = BeginPaint(hWnd, &ps);


        PrintStarCircle(hdc, 400.0f, 400.0f, 300.0f, 80);


        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);


        ReleaseDC(hWnd, hdc);
        break;
    case WM_RBUTTONDOWN:




        InvalidateRect(hWnd, &rc, TRUE);
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
        PostQuitMessage(0);
        break;
    }

    return (DefWindowProc(hWnd, IMessage, wParam, lParam));
}


// 8 / 29
/*
���� 1.
 ������ ���
 -> �������� ������ó�� ���

 -> ��� �� ��� ������ ���� �������� �ﰢ �Լ� X

 ���� 2.
 �簢�� 2�� �����̱�
 -> �� �簢�� ���� : 2��
 -> �ϳ��� ������ �� �ִ� �簢�� / �ٸ� �ϳ��� ������ �� ���� �簢��.
 -> ������ �� ���� �簢���� ������ �� �ִ� �簢���� �о �� ������ �ȴ�.

 ����ó��
 �� 1. 2���� �簢���� ȭ������� ���� �� ����.
 �� 2. 2���� �簢���� �ʱ� ��ġ�� ������ ��ɵ� �߰��Ѵ�.

 �� ���ٸ� ����� �ϱ� ������ �浹 �Լ��� ������� ����.

 ������ ������
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