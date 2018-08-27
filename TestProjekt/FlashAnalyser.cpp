#include "FlashAnalyser.h"



FlashAnalyser::FlashAnalyser()
{
	maFBanBuffer = new CircularBuffer<uint8_t>(1000);
	maFBkatBuffer = new CircularBuffer<uint8_t>(1000);
}


FlashAnalyser::~FlashAnalyser()
{
}

void FlashAnalyser::handleMaFBanData(void * data)
{
	uint8_t dataReceived = *(uint8_t*)data;
	if (!maFBanTriggerFlag) {
		maFBanBuffer->push(dataReceived);
		if (maFBanBuffer->getSize() == 1000 && maFBanTriggerBytesLeft == 0 && dataReceived > 16) {
			maFBanTriggerBytesLeft = 500;
		}
		if (maFBanTriggerBytesLeft > 0) {
			maFBanTriggerBytesLeft--;
			if (maFBanTriggerBytesLeft == 0) {
				maFBanTriggerFlag = true;
			}
		}
	}
	/*if (!maFBanTriggerFlag) {
		maFBanBuffer.push(dataReceived);
		if (maFBanBufferSize<1000) maFBanBufferSize++;
		if (maFBanBufferSize == 1000 && maFBanTriggerBytesLeft == 0 && dataReceived > 16) {
			maFBanTriggerBytesLeft = 500;
		}
		if (maFBanTriggerBytesLeft > 0) {
			maFBanTriggerBytesLeft--;
			if (maFBanTriggerBytesLeft == 0) {
				maFBanTriggerFlag = true;
			}
		}
	}*/
}

void FlashAnalyser::handleMaFBkatData(void * data)
{
	uint8_t dataReceived = *(uint8_t*)data;
	if (!maFBanTriggerFlag)
		maFBkatBuffer->push(dataReceived);

}

void correlateData(CircularBuffer < uint8_t> *bufA, CircularBuffer < uint8_t> *bufB, int32_t *result) {
	uint32_t aDC = 0;
	uint32_t bDC = 0;
	uint32_t aSize = bufA->getSize();
	uint32_t bSize = bufB->getSize();

	for (uint16_t i = 0; i < aSize; i++) {
		aDC+= bufA->read(i);
	}
	for (uint16_t i = 0; i < bSize; i++) {
		bDC+= bufB->read(i);
	}

	aDC /= aSize;
	bDC /= bSize;
	
	for (int16_t i = -bSize; i < aSize; i++) {
		result[i+bSize] = 0;
		for (int j = 0; j < bSize; j++) {
			int32_t bElement = 0;
			if (((i + j) >= 0) && ((i + j) < bSize)) bElement = (int32_t)bufB->read(j + i) - bDC;
			result[i+bSize] += ((int32_t)bufA->read(j) - aDC)*((int32_t)bElement);
		}
	}

	/*
	for (uint16_t i = 0; i < 1000; i++) {
		result[aSize - i-1] = 0;
		for (int j = 0; j < 1000; j++) {
			result[999 - i] += ((int32_t)bufA->read(j) - aDC)*((int32_t)bufB->read(j + i) - bDC);
		}
	}
	for (uint16_t i = 0; i < 1000; i++) {
		result[1000 + i] = 0;
		for (int j = 0; j < 1000; j++) {
			result[1000 + i] += ((int32_t)bufA->read(j + i) - aDC)*((int32_t)bufB->read(j) - bDC);
		}
	}
	*/
}
void FlashAnalyser::analyseData()
{
	if (maFBanTriggerFlag && !once) {
		/*
		uint32_t maFBkatDC = 0;
		uint32_t maFBanDC = 0;

		for (uint16_t i = 0; i < 1000; i++) {
			maFBanDC += maFBanBuffer->read(i);
			maFBkatDC += maFBkatBuffer->read(i);
		}
		maFBanDC /= 1000;
		maFBkatDC /= 1000;
		*/
		int32_t result[3000];
		correlateData(maFBanBuffer, maFBkatBuffer, result);
		/*for (uint16_t i = 0; i < 1000; i++) {
			result[999 - i] = 0;
			for (int j = 0; j < 1000; j++) {
				result[999 - i] += ((int32_t)maFBanBuffer->read(j) - maFBanDC)*((int32_t)maFBkatBuffer->read(j + i) - maFBkatDC);
			}
		}
		for (uint16_t i = 0; i < 1000; i++) {
			result[1000 + i] = 0;
			for (int j = 0; j < 1000; j++) {
				result[1000 + i] += ((int32_t)maFBanBuffer->read(j + i) - maFBanDC)*((int32_t)maFBkatBuffer->read(j) - maFBkatDC);
			}
		}*/

		int32_t largestElement = 0;
		uint16_t largestElementIndex = 0;

		for (uint16_t i = 0; i < 2000; i++) {
			int32_t elementValue = result[i];
			if (elementValue > largestElement) {
				largestElementIndex = i;
				largestElement = elementValue;
			}
		}
		if (triggerCount < 3) {
			triggerCount++;
		}
		else {
			Serial.println("highest correlation value");
			Serial.println(largestElement);

			Serial.println("highest correlation delay in samples");
			Serial.println(largestElementIndex);

			
			Serial.println("");
			Serial.println("**********************");
			Serial.println("Correlation");
			Serial.println("**********************");
			Serial.println("");

			for (uint16_t i = 0; i < 2000; i++) {
			int32_t elementValue = result[i];
			Serial.println(elementValue);
			}

			Serial.println("");
			Serial.println("**********************");
			Serial.println("MaFBanBuffer");
			Serial.println("**********************");
			Serial.println("");

			for (uint16_t i = 0; i < 1000; i++) {
			Serial.println(maFBanBuffer->read(i));
			}
			Serial.println("");
			Serial.println("**********************");
			Serial.println("MaFBkatBuffer");
			Serial.println("**********************");
			Serial.println("");

			for (uint16_t i = 0; i < 1000; i++) {
			Serial.println(maFBkatBuffer->read(i));
			}
			
			Serial.println("");
			once = true;
		}
		maFBanBuffer->setSize(0);
		maFBkatBuffer->setSize(0);

		maFBanTriggerFlag = false;

	}

}
