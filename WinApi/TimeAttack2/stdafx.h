#pragma once

// 4005: �׷��� �������̽� -> ��ũ�� ������ ��� -> �̸� �����ϵ��� ����
#pragma warning(disable : 4005)

// �ڵ� �� ��� ���� -> OS�������� ���� 
// -> API �����ϴ� �Լ����� �ٸ� os�� �������� ������
// �������� �ʿ������ �޸𸮸� ���� ����
#include <SDKDDKVer.h>

 // ���� ������ �ʴ� ������ Windows ������� ��Ȱ��ȭ�մϴ�.
// ole, ole2 ���ӿ����� �ʿ信 ���� ���
// ȸ���� ���� ���� - ���Ϸ� �ޱ�
#define WIN32_LEAN_AND_MEAN
#undef INC_OLE1

// ! Windows ��� ����
#include <Windows.h>

// ! C ��Ÿ�� ���
#include "stdlib.h" // ���Ĵٵ� ���̺귯��
#include <malloc.h> // �����Ҵ� malloc, free (C���� �����ڰ� �� �Ҹ�, C�� Ŭ������ �����ϱ� <-> new�� �Ҹ���)
#include <memory.h> // �޸� ���ۿ� ���� memcpy() �޸� ���� / memset() �޸� ���� / memmove()
#include <stdio.h> // ����� ���̺귯��
#include <tchar.h> // ���ڼ��� �߰������� �ٲ��ִ� ��ũ�ΰ� ����ִ� �������
// MBCS ��Ƽ����Ʈ ĳ���ͼ� (�ƽ�Ű �ƴ� ���� 2����Ʈ) / WBCS ���̵� ����Ʈ ĳ���ͼ� (���� 2����Ʈ)

// ! C++ ��Ÿ�� ��� ����
#include <iostream> // �����
// C++ 11 �߰��� STL -> �پ��� ��� / ���е��� ����(���� �и�)
// �� OS�� ���������� �����Ѵٴ� ������ ���� �޸�Ʈ�� �ִ�.

#include <chrono> 
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <bitset>

using std::vector;
using std::string;
using std::wstring;


// # ���� ���� ��� ���� #
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"

// # ������ ���� #
#define RND RandomFunction::getSingleton() // ������������ ��ũ�� �̸��� Ǯ�������� ���������� �ۼ� (RANDOMFUNCTION)
#define KEYMANAGER KeyManager::getSingleton()

// # ��ũ�� #

#define WINNAME			(LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X		200
#define WINSTART_Y		200
#define WINSIZE_X		800
#define WINSIZE_Y		800
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

// # ��ũ�� �Լ� #
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}


// # ���� ���� #
// extern: ������ ���� �������� ����� (������ ���� ������ �ǹ��ϴ°� �ƴ�, �Լ� ����ο� ������)
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;