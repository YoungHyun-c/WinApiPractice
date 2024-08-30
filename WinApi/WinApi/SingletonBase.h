#pragma once

// 싱글톤 : 프로젝트 전체에서 1개만 존재해야 하는 객체 / 클래스 -> 또는 공유하는 클래스.
// 장 : 인스턴스 생성X -> 메모리의 사용이 적어 효율이 좋다.
// 단 : 결합도.
// SingletonBase

// template, getter, setter 같은 경우엔 헤더에서 구현
template <class T>
class SingletonBase
{
protected:
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	static T* getSingleton(void);
	void releaseSingleton(void);
};

template <typename T>
T* SingletonBase<T>::singleton = 0;

// 가져오는 함수
template <typename T>
T* SingletonBase<T>::getSingleton(void)
{
	if (!singleton) singleton = new T;

	return singleton;
}

template <typename T>
void SingletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}