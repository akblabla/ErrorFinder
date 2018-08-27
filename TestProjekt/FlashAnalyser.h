#pragma once
#include <stdlib.h>
#include <Arduino.h>
#include "CircularBuffer.h"
#include "CircularBufferDynamic.h"

class FlashAnalyser
{
public:
	FlashAnalyser();
	~FlashAnalyser();
	void handleMaFBanData(void * data);
	void handleMaFBkatData(void * data);
	void analyseData();
private:
	bool maFBanTriggerFlag;
	uint16_t maFBanBufferSize;
	CircularBuffer<uint8_t> *maFBanBuffer;
	uint16_t maFBanTriggerBytesLeft;

	uint16_t maFBkatBufferSize;
	CircularBuffer<uint8_t> *maFBkatBuffer;
	uint16_t triggerCount;
	bool once = false;

};

