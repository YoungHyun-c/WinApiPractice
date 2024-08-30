#pragma once

// �̱��� : ������Ʈ ��ü���� 1���� �����ؾ� �ϴ� ��ü / Ŭ���� -> �Ǵ� �����ϴ� Ŭ����.
// �� : �ν��Ͻ� ����X -> �޸��� ����� ���� ȿ���� ����.
// �� : ���յ�.
// SingletonBase

// template, getter, setter ���� ��쿣 ������� ����
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

// �������� �Լ�
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