#pragma once

#pragma warning(disable : 4005)

#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <stdlib.h>
#include <malloc.h>

#include <memory>
#include <malloc.h>

#include <memory>
#include <stdio.h>
#include <tchar.h>

#include <iostream>

#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>

#include "CommonMacroFunction.h"
#include "RandomFunction.h"

#define RND RandomFunction::getSingleton()

#define WINNAME (LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X 400
#define WINSTART_Y 400
#define WINSIZE_X 800
#define WINSIZE_Y 800
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p) {if (p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)	{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;