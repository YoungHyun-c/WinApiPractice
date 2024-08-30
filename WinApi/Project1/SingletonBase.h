#pragma once

template <class T>
class SingleTon
{
protected:
	static T* singleton;

	SingleTon() {}
	~SingleTon() {}

public:
	static T* getSingleton(void);
	void releaseSingleton(void);

};

template <typename T>
T* SingleTon<T>::singleton = 0;

template <typename T>
T* SingleTon<T>::getSingleton(void)
{
	if (!singleton)
	{
		singleton = new T;
	}
	return singleton;
}

template <typename T>
void SingleTon<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}