#include "CircularBuffer.h"
CircularBuffer::CircularBuffer()
{
}

CircularBuffer::~CircularBuffer()
{
}

uint16_t CircularBuffer::push(uint16_t value)
{
	_currentIndex = (_currentIndex+1) % SIZE;
	uint16_t prevValue = _buffer[_currentIndex];
	_buffer[_currentIndex] = value;
	return prevValue;
}

uint16_t CircularBuffer::read(unsigned int index)
{
	return _buffer[(_currentIndex - index) % SIZE];
}

unsigned int CircularBuffer::getCurrentIndex()
{
	return _currentIndex;
}

unsigned int CircularBuffer::getSize()
{
	return SIZE;
}
