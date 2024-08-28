#include <Windows.h>
#include <tchar.h>
#include <cmath>


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
    case 0: // �̸� ȫ
        {
            MoveToEx(hdc, 60, 40, NULL);
            LineTo(hdc, 180, 40);

            MoveToEx(hdc, 45, 60, NULL);
            LineTo(hdc, 210, 60);

            MyCircle(hdc, 120, 130, 7); // ��

            MoveToEx(hdc, 120, 190, NULL); // |
            LineTo(hdc, 120, 210);

            MoveToEx(hdc, 35, 210, NULL); // ��
            LineTo(hdc, 230, 210);

            MyCircle(hdc, 120, 270, 7); // ��
        }
    break;
    case 1:
        // ��
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
        // ��
        {
            MoveToEx(hdc, 560, 40, NULL);
            LineTo(hdc, 680, 40);

            MoveToEx(hdc, 545, 60, NULL);
            LineTo(hdc, 710, 60);

            MyCircle(hdc, 620, 130, 7); // ��

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
    case WM_CREATE: // ������
        break;
    case WM_PAINT: // �׸��±��
    {
        hdc = BeginPaint(hWnd, &ps);

        // ��� ��.
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