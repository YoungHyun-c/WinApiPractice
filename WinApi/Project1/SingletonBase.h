#pragma

template <class T>
class SingleTonBase
{
protected:
	static T* SingleTon;

public:
	static T* GetSingleTon(void);
	void releaseSingleTon(void);
};

template <typename T>
T* SingleTonBase<T>::SingleTon = 0;

template<typename T>
T* SingleTonBase<T>::GetSingleTon(void)
{
	if (!SingleTon)
	{
		SingleTon = new T;
	}
	return SingleTon;
}

template <typename T>
void relaseSingleTon(void)
{
	if (SingleTon)
	{
		delete SingleTon;
		SingleTon = 0;
	}
}