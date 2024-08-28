#include <Windows.h>
#include <tchar.h>
#include <cmath>


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

void MyCircle(HDC _hdc, float _X, float _Y, float _R)
{
    float R = pow(_R, 2);
    for (int i = 0; i < 361; i++)
    {
        MoveToEx(_hdc, _X + (cos(i) * R), _Y + (sin(i) * R), NULL);
        LineTo(_hdc, _X + 1.0f + (cos(i) * R), _Y + 1.0f + (sin(i) * R));
    }
}

void MyUpHalfCircle(HDC _hdc, float _X, float _Y, float _R)
{
    float R = pow(_R, 2);
    for (int i = 0; i < 181; i++)
    {
        MoveToEx(_hdc, _X + (cos(i) * R), _Y - abs(sin(i) * R), NULL);
        LineTo(_hdc, _X + 1.0f + (cos(i) * R), _Y + 1.0f - abs(sin(i) * R));
    }
}

void MyDownHalfCircle(HDC _hdc, float _X, float _Y, float _R)
{
    float R = pow(_R, 2);
    for (int i = 0; i < 181; i++)
    {
        MoveToEx(_hdc, _X + (cos(i) * R), _Y + abs(sin(i) * R), NULL);
        LineTo(_hdc, _X + 1.0f + (cos(i) * R), _Y + 1.0f + abs(sin(i) * R));
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

            MyCircle(hdc, 120, 130, 7); // ㅎ

            MoveToEx(hdc, 120, 190, NULL); // |
            LineTo(hdc, 120, 210);

            MoveToEx(hdc, 35, 210, NULL); // ㅡ
            LineTo(hdc, 230, 210);

            MyCircle(hdc, 120, 270, 7); // ㅇ
        }
    break;
    case 1:
        // 영
        {
            MyCircle(hdc, 320, 120, 7);

            MoveToEx(hdc, 420, 60, NULL);
            LineTo(hdc, 420, 200);          // |

            MoveToEx(hdc, 390, 110, NULL); // -
            LineTo(hdc, 420, 110);

            MoveToEx(hdc, 390, 150, NULL); // -
            LineTo(hdc, 420, 150);

            MyCircle(hdc, 370, 270, 7);
        }
    break;
    case 2:
        // 현
        {
            MoveToEx(hdc, 560, 40, NULL);
            LineTo(hdc, 680, 40);

            MoveToEx(hdc, 545, 60, NULL);
            LineTo(hdc, 710, 60);

            MyCircle(hdc, 620, 130, 7); // ㅎ

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    
    static int Num = 0;

    RECT rc = { 0 + (250 * Num), 0, (250 + (300 * Num)), 400 };

    switch (IMessage)
    {
    case WM_CREATE: // 생성자
        break;
    case WM_PAINT: // 그리는기능
    {
        hdc = BeginPaint(hWnd, &ps);

        // 가운데 선.
        MoveToEx(hdc, 0, 400, NULL);
        LineTo(hdc, 800, 400);


        MyUpHalfCircle(hdc, 300, 300, 8);
        //MyDownHalfCircle(hdc, 300, 300, 8);


        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);

        PrintMyName(hdc, Num);
        
        ReleaseDC(hWnd, hdc);
        break;
    case WM_RBUTTONDOWN:

        --Num;
        if (Num <= 0)
        {
            Num = 0;
        }
        InvalidateRect(hWnd, &rc , TRUE);

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


// 8 / 28
/*
과제1.
 WinApi 출력
 -> MovetoEx() + LineTo()를 이용할것.
 -> 자기 이름 출력 (한글) + UnrealEngine (영문)
  ㄴ 크기는 800 x 800 기준 화면에 절반을 채우는 크기로 양분할것.

 - 마우스 왼쪽을 누르면 한글자씩 출력 되고, 우 클릭을 하면 한글자씩 지워진다. (이름에만 적용)

 ※ 도형 관련 함수 사용 금지.

 과제2. 구구단

 -> 예외처리 필수
  ㄴ 구구단의 본질 (1단 이하 X / 9단 이상 X)

-> 마우스 왼쪽 클릭을 했을 시 1단씩 출력이 되고, 우클릭을 하면 1단씩 지워진다.
-> 그리고 3단계 마다 개행을 한다.

목요일까지
과제3. 애플 로고 출력. 색깔 잇는 것으로.
-> SetPixel()을 이용해서 만든다.
-> 근성 OK / 반복문 OK / 꼼수 X

한줄 조사.
 -> SetTimer
 -> KillTimer
 -> InvaildateRect -> 1, 2번 과제에 필요할것.

*/