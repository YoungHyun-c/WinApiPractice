#pragma once

#pragma comment(lib, "msimg32.lib")

// 설명 :
class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		int width;
		int height;

		float x;
		float y;
		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;

		IMAGE_LOAD_KIND loadType;
		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;

			x = 0;
			y = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO _imageInfo;
	char* _fileName;
	bool _isTrans;
	COLORREF _transColor;

	BLENDFUNCTION _blendFunction;
	LPIMAGE_INFO _blendImage;

public:
	HRESULT init(int width, int height);

	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT	init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	void initForAlphaBlend(void);

	void setTransColor(bool isTrans, COLORREF transColor);

	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);

	// 클리핑
	void render(HDC hdc, int dextX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void renderWithAlpha(HDC hdc, BYTE alpha);
	void renderWithAlpha(HDC hdc, int destX, int destY, BYTE alpha);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	// 1 인라인 함수
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = (x + _imageInfo->width) / 2;
		_imageInfo->y = (y + _imageInfo->height) / 2;
	}

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->x + _imageInfo->width,
			_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	inline RECT boudingBoxWithFrame(void)
	{
		RECT rc =
		{
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->x + _imageInfo->frameWidth,
			_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	inline int getCurrentFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setCurrentFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX < 0)
		{
			_imageInfo->currentFrameX = 0;
		}
		else if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline int getCurrentFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setCurrentFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY < 0)
		{
			_imageInfo->currentFrameY = 0;
		}
		else if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	GImage();
	~GImage() {}
};

