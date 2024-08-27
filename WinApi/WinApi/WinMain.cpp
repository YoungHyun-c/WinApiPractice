// WinApiTest.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#pragma region  WinAPI
/*
�� API (Application Programming Interface)
-> �ü���� ���� ���α׷� ������ ���� �����ϴ� �Լ��� �����̶�� �� �� �ִ�.
-> ��ɾ��� �������� ���ø����̼� ���α׷����� ���۷����� �ý����� �⺻���� ����� ����� �ʿ䰡 ���� ���.
Api���� ��ɾ� ȣ���� ����ȴ�.

EX)
�ϵ� ���� --------------- � ü�� (Windows) -------------- ���� ���α׷�
(API �Լ�) -> ����ڰ� �����쿡�� �ʿ��� ���� �Լ����·� �޾ƿ´�.

�� ��
-> �ü���� ������ ���� ����� ������ ����ϱ⿡ Ȯ�强 �� ������ / �׸��� ���������� �ſ� �����ϴ�.
�� �������� != ������


�� ��
-> ó���ϴ� ���α׷����� ������ ���� �÷����� ���� ����ȭ�� �߻��� �� �ִ�. (WinAPI)
�� C ���� ���ߵ� �÷����� �Ѱ����� �غ����� ���Ѵٴ� ���α׷����� ���.
-> �̴� ��κ��� Ÿ ���̺귯�� Ȯ������ �ذ��� ������, ���α׷����� ������ ���� �䱸�ϱ� ������
    �̴� ������忡���� �����̶�� �� �� �ִ�.

�� API ����
-> ũ�� 3������ ����ϸ� OK
-> ������ / ���� (�޼���) / Window Procedure


*/
#pragma endregion  

#include <Windows.h>
#include <tchar.h>

// ���� ����
/*
 �ν��Ͻ�
 -> ������ OS�� ���� ����ǰ� �ִ� ���α׷��� Ȯ���ϱ� ���� ��.
 -> ���� ���α׷��̸� �Ϲ������� ���� �ν��Ͻ� ���� ������.
 -> Ŭ������ �޸𸮿� ������ ������ ��ü.
 -> ����ǰ� �ִ� ������ ���α׷���.
*/

HINSTANCE _hInstance;
// �ڵ� : ������ â�� �ǹ��Ѵ�.
HWND _hwnd;
// ������ Ÿ��Ʋ
LPTSTR _lpszClass = TEXT("Windows API");
// TCHAR* pszString = _T("Windows API");

/*
LPSTR -> Long Pointer STR  -> char*
LPCSTR -> Long Pointer Const STR -> const char*
LPCTSTR -> const tchar*

�� TCHAR
 -> �� �ڷ����� ������Ʈ ���ڼ� ������ ���� �ڵ������� ��ȯ�� ���ִ� �߰� ��ũ�� �ڷ���
 -> Type Casting �� �����ϸ�, char �Ǵ� Wchar_t�� ��ȯ�Ѵ�.

 -> ��Ƽ�� ���� ȯ�濡�� ������ ���� �۾� ���� ���α׷��� �����ϱ� ���ؼ��� TCHAR������
  ���ڿ��� ǥ���ϴ� ���� �����Ѵ�.

 -> ������ ���ø����̼��� ����ϴ� ���α׷����ʹ� ���� ���α׷����� ���ڿ� ����� ���� ���ؼ��� �߰� ������ ����
 char* -> wchar_t* �� ��ȯ�� ���ִ� _T ��ũ�ε� ��ȿ�ϴ�.

 // ���� ����:
HINSTANCE hInst;
HWND _hwnd;
LPTSTR _lps2Class = TEXT("Windows API");
TCHAR* ps2String = _T("Windows API");

LPCSTR Scrpit1 = "ABC";
LPCWSTR Scrpit2 = L"ABC";
TCHAR* Scrpit3 = _T("ABC"); // �ڵ����� �ٲ� ������, ������ ���� ������.
*/

// �ݹ� �Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
hInstance ���α׷� �ν��Ͻ� �ڵ�
hPrevInstance ������ ����� �ν��Ͻ� �ڵ�
IpszCmdParam ��������� �Է��� ���α׷� ����(��)
nCmdShow ���α׷��� ���۵� ���� (�ּ�ȭ / ���� ũ�� ���...)
*/

// wWinMain world wide�� ���������� �ٲٰڴ�.
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR    lpszCmdParam,
                     int       nCmdShow)
{
    _hInstance = hInstance;

    /*
    winMain�� ����
    �� 1. ������ â�� ���� �� ȭ�鿡 ����.
        -> ȭ�鿡 â�� ���� ���ؼ��� 4���� ó���� ����Ǿ�� �Ѵ�.
    �� 2. �޼��� ����
    */

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
    _hwnd = CreateWindowW
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

    // 1-4 ȭ�鿡 ������â �����ֱ�
    ShowWindow(_hwnd, nCmdShow);
    // ex) �÷��̾��� ��ġ�� �ٲ���� �� ��� ������Ʈ (���ſ�)
    //UpdateWindow(_hwnd);

    // MSG : �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü.
    MSG message;
    // ZeroMemory(&message, nCmdShow);

    // �ڡڡڡڡ�
    // 2. �⺻ �޽��� ����.
    
    // GetMessage : �޼����� ������ �� ���������� ���.
    // �� �޼��� ť�κ��� �ϳ��� �޼����� �������� ������ �����Ѵ�.
    // �� �ٸ� �޼��� ť�� ������� ��� �޼����� ���ö����� ���.

    // - PeekMessage : �޼����� ������ ��ȯ�� �ȴ�. -> ���ӿ��� ���δ�.

    while (GetMessage(&message, 0, 0, 0))
    {
        //if (!TranslateAccelerator(message.hwnd, hAccelTable, &message)) // �õ��ڵ�
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    /*
    TranslateMessage : Ű������ �Է� �޼��� ó���� ����Ѵ�. �Էµ� Ű�� ���� Ű���� Ȯ���ϰ�, �빮�� Ȥ�� �ҹ���,
    �ѱ�, ���������� ���� wM_CHAR �޼����� �߻� ��Ų��.

    DispatchMessage : ������ ���ν������� ���޵� �޼����� ���� ������� �����Ѵ�.
    */

    return (int)message.wParam;
}



//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// ������ ���ν���
// hwnd : ��� �����쿡�� �߻��� �޼��� ���� ����.
// IMessage : �޼��� ���� ��ȣ
// wParam : unsigned int ���콺 ��ư�� ���� / Ű���� ���� Ű�� ���¸� �����Ѵ�.
// lParam : unsigned long ���콺 Ŭ�� ��ǥ�� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    /*
    Window Procedure

    - �޼����� �ü���� ���� -> �ü���� ������ ȣ���� �ȴ�.
       �� WinMain�� �ƴ� �ü���� ���� ȣ���� �Ǵ� �ݹ� �Լ���� �� �� �ִ�.
       �� �����츦 �����Ҷ��� �ݵ�� ������ ���־�� �Ѵ�.

    - ������ ���ν��� ���ο����� �����쿡�� �߻��� ��� �޼����� ó���Ѵ� ���� �ƴ϶� Ư�� �޼������� ó���ϰ�,
    ������ �޼����� DefWindowProc �Լ��� ó���ϵ��� ������ �����ϴ� ���� �Ϲ���.    
    */

    switch (IMessage)
    {
    case WM_CREATE: // ������
        break;
    //case WM_PAINT: // �׸��±��
    //{
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hWnd, &ps);
    //    // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
    //    EndPaint(hWnd, &ps);
    //}
    //break;
    case WM_DESTROY:
        // PostQuitMessage : �� �Լ��� �޼��� ť�� QUIT �޼����� ������ ������ ����.
        // Quit �޼����� �����ϴ� ���� GetMessage�� FALSE�� ��ȯ�ϹǷ� �޼��� ������ ����ȴ�.
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



/*
����1.

���� ����.
- ��Ʈ�� ������ ����´�. (+����)
 �� CallBack Function�� ���ؼ�, DC, GetDC, ReleaseDC, BeginPaint / EndPaint, WM_PAINT, PAINTSTRUCT

 Ÿ�Ӿ���. ������ â �����
 - �ð��� 10��.
 -> ���н� ���� -> ���� �ο� x 2

*/