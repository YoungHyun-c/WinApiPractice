#pragma once

// 4005 : �׷��� �������̽� -> ��ũ�� ���õ� ��� -> �̸� �����ϰڴ�.
#pragma warning(disable : 4005)

// �ڵ� �� ������� ���� -> OS �������� ����.
#include <SDKDDKVer.h>

// ���� ������ �ʴ� ������ Windows ������� ���� �մϴ�. (��Ȱ��ȭ)
#define WIN32_LeAN_AND_MEAN
// #undef // ��ũ�� ���� ����.
//#include <ole.h> -> ȸ�� ���.
//#else
//#include <ole2.h>

// ! Windows ��� ����.
#include <Windows.h>

// ! C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <malloc.h> // �����Ҵ�. �������� ȣ�� ����,
// C�� C++�� ���� C++���� new �ҽ� �����ڿ� ���� ������, C�� ���� Ŭ���� ������ ���⿡, �����Ѹ�ŭ ���� ���־�� �Ѵ�.

#include <memory> // memcpy() / memset() �޸� ���ۿ� ���� ����.
#include <stdio.h>
#include <tchar.h> // ���� ���� �߰������� �ٲ��� �� �ִ� ��ũ�ΰ� ���ִ� ���̺귯��.
// MBCS / WBCS -> Multi Byte Char Set, Wide Byte Char Set

// ! C++ ��Ÿ�� ��� ����
#include <iostream>

// STL -> �پ��� ��� / ���е��� ����. (���� �и�)
// �� OS�� ���������� ������ �Ѵٴ°� ���� �Ÿ�Ʈ�� �ִ�.
#include <chrono>
#include <random>
#include <vector> // erase �� cls
#include <map> // �ڷᱸ���� ����. -> Ʈ������. -> �����Ʈ��.
#include <unordered_map> // �ؽ� �ڷᱸ��. �ؽ�-> �Ϲ��� ��Ȳ������ map���� ���� �� �ִ�.
// �� �� ������ �ϴ� �ߺ� �����͸� ������� �ʴ´�.
// �� �� ���� �����Ͱ� ���ٸ�, �ؽ� �浹 �߻� ���ΰ� �׻� �����Ѵ�.

/*
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dxd11.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

ID2D1Factory* _ID2DFactory = nullptr;
ID2D1HwndRenderTarget* _ID2DRenderTarget = nullptr;
*/

#include "CommonMacroFunction.h"