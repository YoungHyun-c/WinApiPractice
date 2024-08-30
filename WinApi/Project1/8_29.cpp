#include <Windows.h>
#include <tchar.h>
#include <cmath>
#include <iostream>
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
//    // 다항식 계수를 계산한다.
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
    case WM_CREATE: // 생성자
        break;
    case WM_PAINT: // 그리는기능
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
과제 1.
 오망성 출력
 -> 오망성을 마번진처럼 출력

 -> 양식 및 사용 문법은 본인 자유지만 삼각 함수 X

 과제 2.
 사각형 2개 움직이기
 -> 총 사각형 갯수 : 2개
 -> 하나는 움직일 수 있는 사각형 / 다른 하나는 움직일 수 없는 사각형.
 -> 움직일 수 없는 사각형을 움직일 수 있는 사각형이 밀어낼 수 있으면 된다.

 예외처리
 ㄴ 1. 2개의 사각형은 화면밖으로 나갈 수 없다.
 ㄴ 2. 2개의 사각형을 초기 위치로 돌리는 기능도 추가한다.

 ※ 별다른 언급을 하기 전에는 충돌 함수를 사용하지 말것.

 다음주 월요일
 과제 3.
 사각형 영혼 밀어 넣기.

 -> 시작은 큰 사각형 2개와 작은 사각형 1개
 -> 내가 움직일 수 있는 사각형 안에는 작은 사각형이 있다.
 -> 사각형을 움직이면 작은 사각형 역시 움직이거나 / 큰 사각형에 끌려 가야 한다.
 ㄴ 끌려가는 것을 추천.

 -> 예외처리 : 작은 사각형은 큰 사각형을 벗어날 수 없다.

 -> 큰 사각형끼리 충돌이 되면 작은 사각형은 충돌이 된 반대편 사각형으로 이동한다.
 ※ 이때 움직일 수 있는 주도권은 작은 사각형을 소유하고 있는 큰 사각형
 ※ 모서리에 대한 예외처리 수행할 것. -> 작은 사각형과 큰사각형만 고려했을땐 모서리끼리 부딪혔을때 안될 수 있음.
*/