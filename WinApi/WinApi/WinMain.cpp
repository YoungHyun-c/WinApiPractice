// WinApiTest.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
//#include <windowsx.h> // 값이 튈때 사용한다.
#include "MainGame.h"

HINSTANCE _hInstance;
// 핸들 : 윈도우 창을 의미한다.
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
MainGame* _mg;

// 함수
// 콜백 함수
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);

// wWinMain world wide를 진입점으로 바꾸겠다.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    _mg = new MainGame();
    _hInstance = hInstance;

    /*
    winMain의 역할
    ㄴ 1. 윈도우 창을 세팅 후 화면에 띄우기.
        -> 화면에 창을 띄우기 위해서는 4가지 처리가 선행되어야 한다.
    ㄴ 2. 메세지 루프
    */

    // 1-1 윈도우창 구조체 선언 및 초기화
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0; // 클래스에 대한 여분 메모리를 할당 할꺼냐. // 클래스 여분 메모리
    wndClass.cbWndExtra = 0; // 윈도우 ``                             // 윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경색을 정의한다.  // 백그라운드
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                     // 마우스
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // 화면 왼쪽 위의 아이콘을 다른 곳에서 소스를 불러와 띄우겠다. // 아이콘
    wndClass.hInstance = hInstance; // 윈도우 인스턴스                                   // 소유한 식별자 정보.
    wndClass.lpfnWndProc = (WNDPROC)WndProc; // Long Pointer Function Numbering Window Pocedure  // 윈도우 프로시저
    wndClass.lpszClassName = WINNAME; // 윈도우 창 이름.                              // 클래스 이름.
    wndClass.lpszMenuName = NULL; // 우측의 메뉴 상자. (최소화, 닫기) // 메뉴이름.
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                           // 윈도우 스타일

    // 1-2 윈도우 클래스 등록
    RegisterClass(&wndClass);

    // 1-3 화면에 보여줄 윈도우 창 생성.
    _hWnd = CreateWindow
    (
        WINNAME,                 // 윈도우 클래스 식별자
        WINNAME,                 // 윈도우 타이틀 바 이름
        WINSTYLE,        // 윈도우 스타일
        WINSTART_X,                        // 윈도우 화면 X 좌표
        WINSTART_Y,                        // 윈도우 화면 Y 좌표
        WINSIZE_X,                        // 윈도우 화면 가로크기.
        WINSIZE_Y,                        // 윈도우 화면 세로크기
        NULL,         // 부모 윈도우 -> NULL, GetDesktopWindow(), 윈도우 창이 여러개(게임창, 아이템경매장창 등) 필요하면 사용하게 되는 용도이다.
        (HMENU)NULL,                // 메뉴 핸들
        hInstance,                  // 인스턴스 지정
        NULL                        // 윈도우의 자식 윈도우를 생성하면 지정 / 아니라면 NULL
    );

    SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
    // 1-4 화면에 윈도우창 보여주기
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

// 렌더링 최적화를 위해서 사용되는 Z 오더.
void SetWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    // 실제 윈도우 크기 조정.
    // AdjustWindowRect() : RECT 구조체, 원 스타일, 메뉴여부
    AdjustWindowRect(&rc, WINSTYLE, false);

    // 렉트의 정보로 윈도우 사이즈 세팅.
    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

}
