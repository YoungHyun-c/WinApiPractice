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
RECT RC2;
HDC hdc;
RECT InitRCPos = { 400, 400, 100, 100 };
RECT InitRc2Pos = { 500, 500, 100, 100 };
int2 NextPos = {};
int2 RC2Pos = {};
LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch (IMessage)
    {
    case WM_CREATE: // 생성자
        RC = RectMakeCenter(InitRCPos.left, InitRCPos.top, InitRCPos.right, InitRCPos.bottom);
        RC2 = RectMake(InitRc2Pos.left, InitRc2Pos.top, InitRc2Pos.right, InitRc2Pos.bottom);
        break;
    case WM_PAINT: // 그리는기능
    {
        hdc = BeginPaint(hWnd, &ps);

        Rectangle(hdc, RC2.left, RC2.top, RC2.right, RC2.bottom);
        Rectangle(hdc, RC.left, RC.top, RC.right, RC.bottom);

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
            }
            if (CheckCollision(RC, RC2) && IsScreenOver({ RC2.left, RC2.top }))
            {
                RC2.left -= 10;
                RC2.right -= 10;
                if (RC2.left <= 0)
                {
                    RC2.left = 0;
                    RC2.right += 10;
                }
                if (RC.left <= RC2.right)
                {
                    RC.left = RC2.right;
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
            }
            if (CheckCollision(RC, RC2) && IsScreenOver({ RC2.right, RC2.top }))
            {
                RC2.right += 10;
                RC2.left += 10;

                if (RC2.right >= 790)
                {
                    RC2.right = 790;
                    RC2.left -= 10;
                }
                if (RC.right >= RC2.left)
                {
                    RC.right = RC2.left;
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
            }
            if (CheckCollision(RC, RC2) && IsScreenOver({ RC2.left, RC2.top }))
            {
                RC2.top -= 10;
                RC2.bottom -= 10;

                if (RC2.top <= 0)
                {
                    RC2.top = 0;
                    RC2.bottom += 10;
                }
                if (RC.top <= RC2.bottom)
                {
                    RC.top = RC2.bottom;
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
            }
            if (CheckCollision(RC, RC2) && IsScreenOver({ RC2.left, RC2.bottom }))
            {
                RC2.bottom += 10;
                RC2.top += 10;

                if (RC2.bottom >= 760)
                {
                    RC2.bottom = 760;
                    RC2.top = RC2.bottom - 100;
                }
                if (RC.bottom >= RC2.top)
                {
                    RC.bottom = RC2.top;
                    RC.top = RC.bottom - 100;
                }
            }
            break;
        case 'R':
        case 'r':
            RC = RectMakeCenter(InitRCPos.left, InitRCPos.top, InitRCPos.right, InitRCPos.bottom);
            RC2 = RectMake(InitRc2Pos.left, InitRc2Pos.top, InitRc2Pos.right, InitRc2Pos.bottom);
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
