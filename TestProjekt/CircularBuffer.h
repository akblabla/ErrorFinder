#pragma once
#include <vector>
/**
a version of the class "CircularBuffer" that stores the data in the heap instead of the stack
*/
template <typename T>
class CircularBuffer
{
public:
	CircularBuffer() {}
	CircularBuffer(unsigned int capacity) {
		_capacity = capacity;
		_buffer.reserve(_capacity);
		_size = 0;
	}
	virtual ~CircularBuffer() {}
	/**
	*Push an element into the circular buffer, overriding the oldest data in the buffer.
	*@param value the value of the element to be pushed.
	*@return the value of the element overriden.
	*/
	T push(T value)
	{
		if (_size < _capacity) _size++;
		_currentIndex = (_currentIndex + 1) % _capacity;
		T prevValue = _buffer[_currentIndex];
		_buffer[_currentIndex] = value;
		return prevValue;
	}
	/**
	*returns the element at the specified index.
	*@param index the index of the element to be read, with index 0 being the newest element.
	*/
	T read(unsigned int index)
	{
		return _buffer[(_currentIndex - index) % _capacity];
	}
	unsigned int getCurrentIndex()
	{
		return _currentIndex;
	}
	T setAll(T value) {
		for (int i = 0; i < _capacity; i++) {
			_buffer[i] = value;
		}
	}
	void setSize(unsigned int size)
	{
		_size = size;
	}
	void setCapacity(unsigned int capacity)
	{
		_capacity = capacity;
		_buffer.reserve(_capacity);
	}
	/**
	*Gets the size of the circular buffer, which is the amount of elements it can contain.
	**/
	unsigned int getSize()
	{
		return _size;
	}

	unsigned int getCapacity()
	{
		return _capacity;
	}

private:
	std::vector<T> _buffer;
	unsigned int _size;
	unsigned int _capacity;
	unsigned int _currentIndex = 0;
};