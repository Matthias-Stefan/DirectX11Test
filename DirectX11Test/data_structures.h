#pragma once

#include <stdexcept>

//TODO(matthias): POP lead to undefined behavior!

template<typename T>
class Queue
{
public:
	Queue();
	Queue(int Size);

	void Push(T Element);
	T Pop();
	T Front();
	

private:
	bool CheckEnlarge();
	bool CheckReduce();
	void EnlargeArray();
	void ReduceArray();

private:
	T* Elements;

private:
	bool AutoResize;
	int Size;
	int MaxSize;
	int ThresholdEnlarge;
	int ThresholdReduce;
};
template<typename T>
inline Queue<T>::Queue()
	: Size(0), MaxSize(2)
{
	
}


template<typename T>
inline Queue<T>::Queue(int Size)
	: Size(0), MaxSize(Size)
{
	if (Size > 0)
	{
		Elements = new T[Size];
		ThresholdEnlarge = static_cast<float>(MaxSize) * 0.75f;
		ThresholdReduce = static_cast<float>(MaxSize) * 0.25;
	}
}

template<typename T>
inline void Queue<T>::Push(T Element)
{
	Elements[Size] = Element;
	++Size;
	if (CheckEnlarge())
	{
		EnlargeArray();
	}
}

template<typename T>
inline T Queue<T>::Pop()
{
	T Result = Elements[0];
	memmove(Elements, Elements + 1, (Size-1) * sizeof(T));
	--Size;
	if (CheckReduce())
	{
		ReduceArray();
	}
	return Result;
}

template<typename T>
inline T Queue<T>::Front()
{
	T Result = Elements[0];
	return Result;
}


template<typename T>
inline bool Queue<T>::CheckEnlarge()
{
	if (Size > ThresholdEnlarge)
	{
		return true;
	}
	return false;
}

template<typename T>
inline bool Queue<T>::CheckReduce()
{
	if (Size < ThresholdReduce)
	{
		return true;
	}
	return false;
}

template<typename T>
inline void Queue<T>::EnlargeArray()
{
	MaxSize *= 2;
	ThresholdEnlarge = static_cast<float>(MaxSize) * 0.75f;
	ThresholdReduce = static_cast<float>(MaxSize) * 0.25;

	T* EnlargedElements = new T[MaxSize];
	memcpy(EnlargedElements, Elements, Size * sizeof(T));
	delete Elements;
	Elements = EnlargedElements;
	EnlargedElements = nullptr;
}

template<typename T>
inline void Queue<T>::ReduceArray()
{
	MaxSize *= 0.5;
	ThresholdEnlarge = static_cast<float>(MaxSize) * 0.75f;
	ThresholdReduce = static_cast<float>(MaxSize) * 0.25;

	T* ReducedElements = new T[MaxSize];
	memcpy(ReducedElements, Elements, Size * sizeof(T));
	delete Elements;
	Elements = ReducedElements;
	ReducedElements = nullptr;
}
