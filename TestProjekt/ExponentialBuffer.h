#pragma once
#include "CircularBuffer.h"
#include <stdlib.h>
#include <stdint.h>
#define EXPONENTIAL_BUFFER_SIZE 3
class ExponentialBuffer
{
public:
	ExponentialBuffer();
	~ExponentialBuffer();
	unsigned int push(uint16_t value);
	uint16_t read(uint16_t index, uint16_t timeScaleExponent);

private:
	CircularBuffer<uint16_t> _bufferArray[EXPONENTIAL_BUFFER_SIZE];
	uint16_t _exponent;

};

