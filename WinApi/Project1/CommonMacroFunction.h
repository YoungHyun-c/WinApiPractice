#pragma once
// CommonMacroFunction
#include <Windows.h>

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}


// 내가 쓰려고 만든거
inline void MakeCoordi(HDC hdc, int _XSize, int _YSize)
{
	for (int i = 0; i < _XSize; i++)
	{
		MoveToEx(hdc, 0, 100 * i, NULL);
		LineTo(hdc, _YSize, 100 * i);

		MoveToEx(hdc, 100 * i, 0, NULL);
		LineTo(hdc, 100 * i, _YSize);
	}
}