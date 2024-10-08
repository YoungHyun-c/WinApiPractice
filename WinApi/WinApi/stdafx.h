#pragma once

// 4005 : 그래픽 인터페이스 -> 매크로 관련된 경고 -> 이를 무시하겠다.
#pragma warning(disable : 4005)

// 코드 및 상수제어 제어 -> OS 레벨에서 관리.
#include <SDKDDKVer.h>

// 거의 사용되지 않는 내용을 Windows 헤더에서 제외 합니다. (비활성화)
#define WIN32_LEAN_AND_MEAN
#undef INC_OLE1
// #undef // 매크로 지정 해제.
//#include <ole.h> -> 회전 헤더.
//#else
//#include <ole2.h>

// ! Windows 헤더 파일.
#include <Windows.h>

// ! C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h> // 동적할당. 생성자의 호출 여부,
// C와 C++의 차이 C++에선 new 할시 생성자에 들어가게 되지만, C의 경우는 클래스 개념이 없기에, 지정한만큼 해제 해주어야 한다.

#include <memory> // memcpy() / memset() 메모리 조작에 관한 내용.
#include <stdio.h>
#include <tchar.h> // 문자 셋을 중간형으로 바꿔줄 수 있는 매크로가 들어가있는 라이브러리.
// MBCS / WBCS -> Multi Byte Char Set, Wide Byte Char Set

// ! C++ 런타임 헤더 파일
#include <iostream>

// STL -> 다양한 기능 / 정밀도가 높다. (나노 밀리)
// ㄴ OS와 독립적으로 동작을 한다는게 아주 매리트가 있다.
#include <chrono>
#include <random>
#include <vector> // erase 와 cls
#include <map> // 자료구조에 대해. -> 트리구조. -> 레드블랙트리.
#include <unordered_map> // 해쉬 자료구조. 해쉬-> 일반적 상황에서는 map보다 빠를 수 있다.
// ㄴ 그 이유는 일단 중복 데이터를 허용하지 않는다.
// ㄴ 단 유사 데이터가 많다면, 해시 충돌 발생 여부가 항상 존재한다.
#include <bitset>

using std::bitset;
using std::vector;
using std::string;
using std::wstring;

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

// Stdafx (Standard Application FrameWorks)
// ㄴ VS를 이용하여 프로젝트를 생성하면 생성되는 클래스 약어 -> MS
// ㄴ 표준 어플리케이션 프레임워크 툴

// # 내가 만든 헤더 파일 #
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"

// # 디자인 패턴 #
#define RND RandomFunction::getSingleton() // 왠만하면, 매크로가 아닌 것은 풀네임으로, 대문자로 써야된다. 언더바없이.
#define KEYMANAGER KeyManager::getSingleton()

// # 매크로 #
#define WINNAME			(LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X		200
#define WINSTART_Y		200
#define WINSIZE_X		1024
#define WINSIZE_Y		768
#define WINSTYLE		WS_CAPTION | WS_SYSMENU // 타이틀바, 오른쪽 메뉴

// # 매크로 함수 #
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

// # 전역 변수 #
// extern -> 명시 키워드 함수의 선언 부분과 비슷하다. 선언 되어있으니 오류처리하지말구 넘어가라.
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
