/*
 Name:		TestProjekt.ino
 Created:	8/7/2018 10:35:16 AM
 Author:	Anders
*/

#include "ADC.h"
#include "DataAnalyser.h"
#include "Timer.h"
ADC *adc = new ADC(); // adc object;
Timer timer;
uint32_t useconds;
uint32_t sampleRate;
float output[20];
uint8_t ADC_0_lastReadPIN;



void errorHandler(errorType e) {
	if (e == errorType::flashOver) Serial.println("FLASHOVER!");
}

DataAnalyser dataAnalyser(errorHandler);


void setup() {
	adc->setAveraging(8, ADC_0); // set number of averages
	adc->setAveraging(16, ADC_1); // set number of averages
	adc->setResolution(8, ADC_0); // set bits of resolution
	adc->setResolution(16, ADC_1); // set bits of resolution
	adc->setReference(ADC_REFERENCE::REF_3V3, ADC_0);
	adc->setConversionSpeed(ADC_CONVERSION_SPEED::MED_SPEED, ADC_0); // change the conversion speed
	adc->setConversionSpeed(ADC_CONVERSION_SPEED::MED_SPEED, ADC_1); // change the conversion speed
	adc->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED, ADC_0); // change the sampling speed
	adc->setSamplingSpeed	(ADC_SAMPLING_SPEED::MED_SPEED, ADC_1); // change the sampling speed

	//adc->startContinuous(14, ADC_0);
	adc->startSingleRead(dataChannel::maFBan, ADC_0);
	ADC_0_lastReadPIN = dataChannel::maFBan;

	adc->startSingleRead(dataChannel::htDrivePushPullCurrent, ADC_1);


	//adc->startSingleRead(31, ADC_1);
	pinMode(13, OUTPUT);
	Serial.begin(115200);
	adc->enableInterrupts(ADC_0);
	adc->enableInterrupts(ADC_1);
/*	CircularBuffer<uint16_t, 1000> buf;
	buf.setAll(0);
	for (int i = 0; i < 3200; i++) {
		buf.push(i);
	}
	for (int i = 0; i < 1000; i++) {
		
		Serial.println(buf.read(i));
	}*/
}// the loop function runs over and over again until power down or reset 
uint16_t data;
uint16_t largestData;
void loop() {
	//Serial.println(sampleRate*2);
//	Serial.println(data);
	largestData = 0;
	sampleRate = 0;
	dataAnalyser.analyseData();
	delay(50);
}

int outputPin;
void adc0_isr(void) {
	
	uint8_t pinToRead;
	if (ADC_0_lastReadPIN == dataChannel::maFBan) pinToRead = dataChannel::maFBkat;
	if (ADC_0_lastReadPIN == dataChannel::maFBkat) pinToRead = dataChannel::maFBan;

	data = adc->readSingle(ADC_0);
	adc->startSingleRead(pinToRead, ADC_0);
	dataAnalyser.iterateData(&data, ADC_0_lastReadPIN);
	ADC_0_lastReadPIN = pinToRead;
	
}

void adc1_isr(void) {
	sampleRate++;
	data = adc->readSingle(ADC_1);
	adc->startSingleRead(dataChannel::htDrivePushPullCurrent, ADC_1);
	dataAnalyser.iterateData(&data, dataChannel::htDrivePushPullCurrent);
}