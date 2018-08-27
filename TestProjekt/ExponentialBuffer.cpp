#include "ExponentialBuffer.h"
#include <Arduino.h>


ExponentialBuffer::ExponentialBuffer()
{
	_exponent = 512;

}


ExponentialBuffer::~ExponentialBuffer()
{
}

unsigned int ExponentialBuffer::push(uint16_t value)
{
	_bufferArray[0].push(value);
	unsigned int i = 0;
	while ((_bufferArray[i].getCurrentIndex()%_exponent == 0)&&(i<(EXPONENTIAL_BUFFER_SIZE-1))) {
		uint32_t averageValue = 0;
		for (int j = 0; j < _exponent; j++) {
			averageValue += _bufferArray[i].read(j);
		}
		averageValue = averageValue/_exponent;
		_bufferArray[i+1].push((uint16_t)averageValue);
		i++;
	}
	return i;

}

uint16_t ExponentialBuffer::read(uint16_t index, uint16_t timeScaleExponent)
{
	return _bufferArray[timeScaleExponent].read(index);
}