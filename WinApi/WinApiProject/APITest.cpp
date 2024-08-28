#include <Windows.h>
#include <tchar.h>
#include <cmath>

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

void PrintMyName(HDC hdc, int& _Num)
{
    switch (_Num)
    {
    case 0: // �̸� ȫ
        {
            MoveToEx(hdc, 60, 40, NULL);
            LineTo(hdc, 180, 40);

            MoveToEx(hdc, 45, 60, NULL);
            LineTo(hdc, 210, 60);

            MyCircle(hdc, 120, 130, CirCleSize); // ��

            MoveToEx(hdc, 120, 190, NULL); // |
            LineTo(hdc, 120, 210);

            MoveToEx(hdc, 35, 210, NULL); // ��
            LineTo(hdc, 230, 210);

            MyCircle(hdc, 120, 270, CirCleSize); // ��
        }
    break;
    case 1:
        // ��
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
        // ��
        {
            MoveToEx(hdc, 560, 40, NULL);
            LineTo(hdc, 680, 40);

            MoveToEx(hdc, 545, 60, NULL);
            LineTo(hdc, 710, 60);

            MyCircle(hdc, 620, 130, CirCleSize); // ��

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
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    
    static int Num = 0;

    RECT rc = { 0 + (250 * Num), 0, (250 + (300 * Num)), 400 };

    

    switch (IMessage)
    {
    case WM_CREATE: // ������
        break;
    case WM_PAINT: // �׸��±��
    {
        hdc = BeginPaint(hWnd, &ps);

        // ��� ��.
        MoveToEx(hdc, 0, 400, NULL);
        LineTo(hdc, 800, 400);
        // Unreal Engine
        {
            PrintUnreal(hdc);
        }
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
����1.
 WinApi ���
 -> MovetoEx() + LineTo()�� �̿��Ұ�.
 -> �ڱ� �̸� ��� (�ѱ�) + UnrealEngine (����)
  �� ũ��� 800 x 800 ���� ȭ�鿡 ������ ä��� ũ��� ����Ұ�.

 - ���콺 ������ ������ �ѱ��ھ� ��� �ǰ�, �� Ŭ���� �ϸ� �ѱ��ھ� ��������. (�̸����� ����)

 �� ���� ���� �Լ� ��� ����.

 ����2. ������

 -> ����ó�� �ʼ�
  �� �������� ���� (1�� ���� X / 9�� �̻� X)

-> ���콺 ���� Ŭ���� ���� �� 1�ܾ� ����� �ǰ�, ��Ŭ���� �ϸ� 1�ܾ� ��������.
-> �׸��� 3�ܰ� ���� ������ �Ѵ�.

����ϱ���
����3. ���� �ΰ� ���. ���� �մ� ������.
-> SetPixel()�� �̿��ؼ� �����.
-> �ټ� OK / �ݺ��� OK / �ļ� X

���� ����.
 -> SetTimer
 -> KillTimer
 -> InvaildateRect -> 1, 2�� ������ �ʿ��Ұ�.

*/