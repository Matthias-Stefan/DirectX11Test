#pragma once

#include <stdexcept>

template<typename T>
class Queue
{
public:
	Queue() = delete;
	Queue(int Size);

	bool Push(T Element);
	T Pop();

private:
	bool CheckEnlarge();
	bool CheckReduce();

private:
	T* Elements;

private:
	int Size;
	int MaxSize;
	int ThresholdEnlarge;
	int ThresholdReduce;
};

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
inline bool Queue<T>::Push(T Element)
{
	Elements[Size] = Element;
	++Size;
	CheckEnlarge();
	return true;
}

template<typename T>
inline T Queue<T>::Pop()
{
	T Result = Elements[0];
	memmove(Elements, Elements + 1, Size * sizeof(T));
	return Result;
}



template<typename T>
inline bool Queue<T>::CheckEnlarge()
{
	if (Size > ThresholdEnlarge)
	{
		MaxSize *= 2;
		ThresholdEnlarge = static_cast<float>(MaxSize) * 0.75f;
		ThresholdReduce = static_cast<float>(MaxSize) * 0.25;

		T* EnlargedElements = new T[MaxSize];
		memcpy(EnlargedElements, Elements, Size*sizeof(T));
		delete Elements;
		Elements = EnlargedElements;
		EnlargedElements = nullptr;
		
		return true;
	}
	return true;
}

template<typename T>
inline bool Queue<T>::CheckReduce();
