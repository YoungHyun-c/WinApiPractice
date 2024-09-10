#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include "CommonMacroFunction.h"

#define CirCleSize 50

HINSTANCE _hInstance;
// 핸들 : 윈도우 창을 의미한다.
HWND _hwnd;
// 윈도우 타이틀
LPTSTR _lpszClass = TEXT("Windows API");
// TCHAR* pszString = _T("Windows API");

// 콜백 함수
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// wWinMain world wide를 진입점으로 바꾸겠다.
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR    lpszCmdParam,
    int       nCmdShow)
{
    _hInstance = hInstance;


    // 1-1 윈도우창 구조체 선언 및 초기화
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0; // 클래스에 대한 여분 메모리를 할당 할꺼냐. // 클래스 여분 메모리
    wndClass.cbWndExtra = 0; // 윈도우 ``                             // 윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경색을 정의한다.  // 백그라운드
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                     // 마우스
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // 화면 왼쪽 위의 아이콘을 다른 곳에서 소스를 불러와 띄우겠다. // 아이콘
    wndClass.hInstance = hInstance; // 윈도우 인스턴스                                   // 소유한 식별자 정보.
    wndClass.lpfnWndProc = (WNDPROC)WndProc; // Long Pointer Function Numbering Window Pocedure  // 윈도우 프로시저
    wndClass.lpszClassName = _lpszClass; // 윈도우 창 이름.                              // 클래스 이름.
    wndClass.lpszMenuName = NULL; // 우측의 메뉴 상자. (최소화, 닫기) // 메뉴이름.
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                           // 윈도우 스타일

    // 1-2 윈도우 클래스 등록
    RegisterClass(&wndClass);

    // 1-3 화면에 보여줄 윈도우 창 생성.
    _hwnd = CreateWindow
    (
        _lpszClass,                 // 윈도우 클래스 식별자
        _lpszClass,                 // 윈도우 타이틀 바 이름
        WS_OVERLAPPEDWINDOW,        // 윈도우 스타일
        400,                        // 윈도우 화면 X 좌표
        100,                        // 윈도우 화면 Y 좌표
        800,                        // 윈도우 화면 가로크기.
        800,                        // 윈도우 화면 세로크기
        NULL,         // 부모 윈도우 -> NULL, GetDesktopWindow(), 윈도우 창이 여러개(게임창, 아이템경매장창 등) 필요하면 사용하게 되는 용도이다.
        (HMENU)NULL,                // 메뉴 핸들
        hInstance,                  // 인스턴스 지정
        NULL                        // 윈도우의 자식 윈도우를 생성하면 지정 / 아니라면 NULL
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

struct Color
{
    static const int WHITE;
    static const int BLUE;
    static const int GREEN;
    static const int RED;
    static const int YELLOW;
    static const int ORANGE;
    static const int PURPLE;
};

const int Color::WHITE = 0xFFFFFF;
const int Color::BLUE = 0xFF0000;
const int Color::GREEN = 0x00FF00;
const int Color::RED = 0x0000FF;
const int Color::YELLOW = 0x33CCFF;
const int Color::ORANGE = 0x3399FF;
const int Color::PURPLE = 0x9900CC;

#define White_Color int3(255,255,255)

void PrintWhiteCustomCircle(HDC hdc, float _X, float _Y, float _R, float _Rate = 40.0f)
{
    float Rpow = static_cast<float>(pow(_R, 2));

    for (float X = _X - _R; X < _X + _R; X++)
    {
        for (float Y = _Y - _R; Y < _Y + _R; Y++)
        {
            float Xpow = ((_X - X) * (_X - X)) / 2;
            float Ypow = (_Y - Y) * (_Y - Y);

            if (Xpow + Ypow <= Rpow)
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), Color::WHITE);
            }
        }
    }
}

void PrintWhiteCircle(HDC hdc, float _X, float _Y, float _R, float _Rate = 40.0f)
{
    float Rpow = static_cast<float>(pow(_R, 2));

    for (float X = _X - _R; X < _X + _R; X++)
    {
        for (float Y = _Y - _R; Y < _Y + _R; Y++)
        {
            float Xpow = ((_X - X) * (_X - X));
            float Ypow = (_Y - Y) * (_Y - Y);

            if (Xpow + Ypow <= Rpow)
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), Color::WHITE);
            }
        }
    }
}

#define LeafCircle 75
bool CollisionCheck(float _X, float _Y, float _OtherX, float _OtherY)
{
    double distance = sqrt(pow(_OtherX - _X, 2) + pow(_OtherY - _Y, 2));
    return distance < (LeafCircle + LeafCircle);
}

void PrintCircle(HDC hdc, float _X, float _Y, float _R, float _Rate = 40.0f, int _Color = 0xFFFFFF)
{
    float Rpow = static_cast<float>(pow(_R, 2));
    for (float X = _X - _R; X < _X + _R; X++)
    {
        for (float Y = _Y - _R; Y < _Y + _R; Y++)
        {
            float Xpow = (_X - X) * (_X - X);
            float Ypow = (_Y - Y) * (_Y - Y);
            if (Y <= 267 && Xpow + Ypow <= Rpow)
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), Color::GREEN);
            }
            else if (Y <= 334 && Xpow + Ypow <= Rpow)
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), Color::YELLOW);
            }
            else if (Y <= 401 && Xpow + Ypow <= Rpow)
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), Color::ORANGE);
            }
            else if (Y <= 468 && Xpow + Ypow <= Rpow)
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), Color::RED);
            }
            else if (Y <= 525 && Xpow + Ypow <= Rpow)
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), Color::PURPLE);
            }
            else if (Xpow + Ypow <= Rpow)
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), _Color);
            }
        }
    }
}

void PrintLeaf(HDC hdc, float _X, float _Y, float _OtherX, float _OtherY, float _R, float _Rate = 40.0f, int _Color = 0xFFFFFF)
{
    float Rpow = static_cast<float>(pow(_R, 2));
    for (float X = _X - _R; X < _X + _R; X++)
    {
        for (float Y = _Y - _R; Y < _Y + _R; Y++)
        {
            float Xpow = (_X - X) * (_X - X);
            float Ypow = (_Y - Y) * (_Y - Y);
            if (Xpow + Ypow <= Rpow && CollisionCheck(X, Y, _OtherX, _OtherY))
            {
                SetPixel(hdc, static_cast<int>(X), static_cast<int>(Y), _Color);
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

    RECT rc = { 0 + (250 * Num), 0, (250 + (300 * Num)), 400 };



    switch (IMessage)
    {
    case WM_CREATE: // 생성자
        break;
    case WM_PAINT: // 그리는기능
    {
        hdc = BeginPaint(hWnd, &ps);

        // x 선.
        for (int i = 0; i < 9; i++)
        {
            MoveToEx(hdc, 0, 100 * i, NULL);
            LineTo(hdc, 800, 100 * i);

            MoveToEx(hdc, 100 * i, 0, NULL);
            LineTo(hdc, 100 * i, 800);
        }

        PrintCircle(hdc, 400.0f, 400.0f, 200, 40, Color::BLUE);
        PrintWhiteCustomCircle(hdc, 400.0f, 640.0f, 80.0f);
        PrintWhiteCustomCircle(hdc, 400.0f, 140.0f, 80.0f);

        PrintCircle(hdc, 300.0f, 300.0f, 100.0f, 40.0f, Color::BLUE);
        PrintCircle(hdc, 320.0f, 350.0f, 140.0f, 40.0f, Color::BLUE);
        PrintCircle(hdc, 300.0f, 400.0f, 110.0f, 40.0f, Color::BLUE);

        PrintCircle(hdc, 500.0f, 300.0f, 100.0f, 40.0f, Color::BLUE);

        PrintCircle(hdc, 335.0f, 535.0f, 50.0f, 40.0f, Color::BLUE);
        PrintCircle(hdc, 465.0f, 535.0f, 50.0f, 40.0f, Color::BLUE);


        PrintLeaf(hdc, 380.0f, 50.0f, 530.0f, 200.0f, 150.0f, 40.0f, Color::GREEN);


        PrintWhiteCircle(hdc, 600.0f, 370.0f, 100.0f);
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
