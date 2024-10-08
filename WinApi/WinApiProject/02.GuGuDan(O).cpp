#include <Windows.h>
#include <tchar.h>
#include <cmath>
#include <iostream>

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

void PrintMyName(HDC hdc, int& _Num)
{
    switch (_Num)
    {
    case 0: // 이름 홍
    {
        MoveToEx(hdc, 60, 40, NULL);
        LineTo(hdc, 180, 40);

        MoveToEx(hdc, 45, 60, NULL);
        LineTo(hdc, 210, 60);

        MyCircle(hdc, 120, 130, CirCleSize); // ㅎ

        MoveToEx(hdc, 120, 190, NULL); // |
        LineTo(hdc, 120, 210);

        MoveToEx(hdc, 35, 210, NULL); // ㅡ
        LineTo(hdc, 230, 210);

        MyCircle(hdc, 120, 270, CirCleSize); // ㅇ
    }
    break;
    case 1:
        // 영
    {
        MyCircle(hdc, 320, 120, CirCleSize);

        MoveToEx(hdc, 420, 60, NULL);
        LineTo(hdc, 420, 200);          // |

        MoveToEx(hdc, 390, 110, NULL); // -
        LineTo(hdc, 420, 110);

        MoveToEx(hdc, 390, 150, NULL); // -
        LineTo(hdc, 420, 150);

        MyCircle(hdc, 370, 270, CirCleSize);
    }
    break;
    case 2:
        // 현
    {
        MoveToEx(hdc, 560, 40, NULL);
        LineTo(hdc, 680, 40);

        MoveToEx(hdc, 545, 60, NULL);
        LineTo(hdc, 710, 60);

        MyCircle(hdc, 620, 130, CirCleSize); // ㅎ

        MoveToEx(hdc, 720, 60, NULL);
        LineTo(hdc, 720, 200);          // |

        MoveToEx(hdc, 690, 110, NULL); // -
        LineTo(hdc, 720, 110);

        MoveToEx(hdc, 690, 150, NULL); // -
        LineTo(hdc, 720, 150);


        MoveToEx(hdc, 590, 220, NULL);
        LineTo(hdc, 590, 270);

        MoveToEx(hdc, 590, 270, NULL);
        LineTo(hdc, 700, 270);
    }
    break;
    }
    ++_Num;
    if (_Num >= 2)
    {
        _Num = 2;
    }
}

void PrintUnreal(HDC hdc)
{
    // U
    MoveToEx(hdc, 50, 450, NULL);
    LineTo(hdc, 50, 520);
    MoveToEx(hdc, 100, 450, NULL);
    LineTo(hdc, 100, 520);
    MyDownHalfCircle(hdc, 75, 520, 25);

    // n
    MoveToEx(hdc, 130, 500, NULL);
    LineTo(hdc, 130, 550);
    MoveToEx(hdc, 180, 500, NULL);
    LineTo(hdc, 180, 550);
    MyUpHalfCircle(hdc, 155, 500, 25);

    // r
    MoveToEx(hdc, 210, 500, NULL);
    LineTo(hdc, 210, 550);
    MyUpHalfCircle(hdc, 235, 525, 25);

    // e
    MoveToEx(hdc, 280, 525, NULL);
    LineTo(hdc, 325, 525);
    MyAngle(hdc, 300, 525, 25, 310);

    // a
    MyUpHalfCircle(hdc, 360, 510, 25);
    MyCircle(hdc, 360, 535, 25);
    MoveToEx(hdc, 385, 510, NULL);
    LineTo(hdc, 385, 555);

    // l
    MoveToEx(hdc, 410, 450, NULL);
    LineTo(hdc, 410, 555);

    // E
    MoveToEx(hdc, 320, 625, NULL);
    LineTo(hdc, 365, 625);
    MoveToEx(hdc, 320, 655, NULL);
    LineTo(hdc, 365, 655);
    MoveToEx(hdc, 320, 685, NULL);
    LineTo(hdc, 365, 685);
    MoveToEx(hdc, 320, 625, NULL);
    LineTo(hdc, 320, 685);

    // n
    MoveToEx(hdc, 400, 655, NULL);
    LineTo(hdc, 400, 680);
    MoveToEx(hdc, 450, 655, NULL);
    LineTo(hdc, 450, 680);
    MyUpHalfCircle(hdc, 425, 660, 25);

    // g
    MyCircle(hdc, 500, 660, 25);
    MoveToEx(hdc, 525, 650, NULL);
    LineTo(hdc, 525, 700);
    MyDownHalfCircle(hdc, 500, 700, 25);

    // i
    MyCircle(hdc, 550, 620, 5);
    MoveToEx(hdc, 550, 640, NULL);
    LineTo(hdc, 550, 690);

    // n
    MoveToEx(hdc, 580, 655, NULL);
    LineTo(hdc, 580, 680);
    MoveToEx(hdc, 630, 655, NULL);
    LineTo(hdc, 630, 680);
    MyUpHalfCircle(hdc, 605, 660, 25);

    //e
    MoveToEx(hdc, 645, 655, NULL);
    LineTo(hdc, 690, 655);
    MyAngle(hdc, 665, 655, 25, 310);


    MoveToEx(hdc, 645, 655, NULL);
    LineTo(hdc, 646, 656);
}

typedef struct { float x, y; } Point2D;

Point2D PointOnCubicBezier(HDC hdc, Point2D* cp, float t)
{
    float ax, bx, cx, ay, by, cy, tSquared, tCubed;
    Point2D result;

    // 다항식 계수를 계산한다.
    cx = 3.0 * (cp[1].x - cp[0].x);
    bx = 3.0 * (cp[2].x - cp[1].x) - cx;
    ax = cp[3].x - cp[0].x - cx - bx;

    cy = 3.0 * (cp[1].y - cp[0].y);
    by = 3.0 * (cp[2].y - cp[1].y) - cy;
    ay = cp[3].y - cp[0].y - cy - by;

    tSquared = t * t;
    tCubed = tSquared * t;

    result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + cp[0].x;
    result.y = (ay * tCubed) + (bx * tSquared) + (cy * t) + cp[0].y;

    MoveToEx(hdc, result.x, result.y, NULL);
    LineTo(hdc, result.x + 2, result.y + 2);
    return result;
}

void Computerbezier(HDC hdc, Point2D* cp, int NumberOfPoints, Point2D* Curve)
{
    float dt;
    int i;

    dt = 1.0 / (NumberOfPoints - 1);

    for (i = 0; i < NumberOfPoints; i++)
        Curve[i] = PointOnCubicBezier(hdc, cp, i * dt);

}

Point2D* Pos1 = new Point2D({ 300, 300 });
Point2D* Pos2 = new Point2D({ 400, 400 });

LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    static int Num = 0;
    static int Dan = 2;

    const int X = 150;
    const int Y = 10;

    char Ch[256];

    RECT rc2 = { X + 150 * (Dan % 3), Y + (240 * (Dan / 3)) ,
         X + (300 * (Dan % 3) + (300 * (Dan / 3))), Y + 240 * ((Dan / 3) + 1)};


    switch (IMessage)
    {
    case WM_CREATE: // 생성자
        break;
    case WM_PAINT: // 그리는기능
    {
        hdc = BeginPaint(hWnd, &ps);


        Computerbezier(hdc, Pos1, 70, Pos2);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);


        // 구구단  
        for (int i = 2; i <= Dan; i++)
        {
            for (int j = 1; j < 10; j++)
            {
                sprintf_s(Ch, "%d x %d = %d", i, j, i * j);
                TextOut(hdc, X + ((i - 1) % 3 * 200),
                    Y + (240 * ((i - 1) / 3) + (j - 1) * 25), Ch, static_cast<int>(strlen(Ch)));
            }
        }
        Dan++;
        if (Dan >= 9)
        {
            Dan = 9;
        }

        ReleaseDC(hWnd, hdc);
        break;
    case WM_RBUTTONDOWN:
        --Num;
        if (Num <= 0)
        {
            Num = 0;
        }

        Dan--;
        if (Dan <= 1)
        {
            Dan = 1;
        }
        InvalidateRect(hWnd, &rc2, TRUE);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
