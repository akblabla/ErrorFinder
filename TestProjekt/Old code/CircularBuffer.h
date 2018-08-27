#pragma once
#include <stdint.h>
#include <vector>
#include <Arduino.h>
/**
A circular buffer that allows elements to be pushed into a buffer, where the oldest elements are replaced as the buffer is filled.
*/
template <typename T, int size>
class CircularBuffer
{
public:
	CircularBuffer() {
	}
	virtual ~CircularBuffer() {}
	/**
	*Push an element into the circular buffer, overriding the oldest data in the buffer.
	*@param value the value of the element to be pushed.
	*@return the value of the element overriden.
	*/
	T push(T value)
	{
		_currentIndex = (_currentIndex + 1) % size;
		T prevValue = _buffer[_currentIndex];
		_buffer[_currentIndex] = value;
		return prevValue;
	}
	/**
	*returns the element at the specified index.
	*@param index the index of the element to be read, with index 0 being the newest element.
	*/
	T read(uint16_t index)
	{
		if (index > getSize() - 1) return 0;
		int32_t realIndex = ((int32_t)_currentIndex - (int32_t)index) % size;
		if (realIndex < 0) realIndex += size;
		return _buffer[realIndex];
	}
	uint16_t getCurrentIndex()
	{
		return _currentIndex;
	}
	T setAll(T value) {
		for (int i = 0; i < size; i++) {
			_buffer[i] = value;
		}
	}
	/**
	*Gets the size of the circular buffer, which is the amount of elements it can contain.
	**/
	unsigned int getSize()
	{
		return size;
	}
private:
	T _buffer[size] = {};
	unsigned int _currentIndex = 0;
};

