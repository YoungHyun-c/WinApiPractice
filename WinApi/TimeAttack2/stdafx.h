#pragma once

// 4005: 그래픽 인터페이스 -> 매크로 관련한 경고 -> 이를 무시하도록 설정
#pragma warning(disable : 4005)

// 코드 및 상수 제어 -> OS레벨에서 관리 
// -> API 지원하는 함수들을 다른 os로 컨버팅을 도와줌
// 컨버팅이 필요없으면 메모리를 먹지 않음
#include <SDKDDKVer.h>

 // 거의 사용되지 않는 내용을 Windows 헤더에서 비활성화합니다.
// ole, ole2 게임에서는 필요에 따라 사용
// 회전에 관한 내용 - 오일러 앵글
#define WIN32_LEAN_AND_MEAN
#undef INC_OLE1

// ! Windows 헤더 파일
#include <Windows.h>

// ! C 런타임 헤더
#include "stdlib.h" // 스탠다드 라이브러리
#include <malloc.h> // 동적할당 malloc, free (C언어는 생성자가 안 불림, C는 클래스가 없으니까 <-> new는 불린다)
#include <memory.h> // 메모리 동작에 대해 memcpy() 메모리 복사 / memset() 메모리 세팅 / memmove()
#include <stdio.h> // 입출력 라이브러리
#include <tchar.h> // 문자셋을 중간형으로 바꿔주는 매크로가 들어있는 헤더파일
// MBCS 멀티바이트 캐릭터셋 (아스키 아닌 것은 2바이트) / WBCS 와이드 바이트 캐릭터셋 (전부 2바이트)

// ! C++ 런타임 헤더 파일
#include <iostream> // 입출력
// C++ 11 추가된 STL -> 다양한 기능 / 정밀도가 높다(나노 밀리)
// ㄴ OS와 독립적으로 동작한다는 점에서 아주 메리트가 있다.

#include <chrono> 
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <bitset>

using std::vector;
using std::string;
using std::wstring;


// # 내가 만든 헤더 파일 #
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"

// # 디자인 패턴 #
#define RND RandomFunction::getSingleton() // 디자인패턴의 매크로 이름은 풀네임으로 정상적으로 작성 (RANDOMFUNCTION)
#define KEYMANAGER KeyManager::getSingleton()

// # 매크로 #

#define WINNAME			(LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X		200
#define WINSTART_Y		200
#define WINSIZE_X		800
#define WINSIZE_Y		800
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

// # 매크로 함수 #
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}


// # 전역 변수 #
// extern: 변수가 전역 변수임을 명시함 (실제로 전역 변수를 의미하는게 아님, 함수 선언부와 유사함)
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;