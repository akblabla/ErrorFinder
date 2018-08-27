#include "TubeEffectAnalyser.h"



TubeEffectAnalyser::TubeEffectAnalyser()
{
}


TubeEffectAnalyser::~TubeEffectAnalyser()
{
}

void TubeEffectAnalyser::analyseData()
{/*
	Serial.println("*****************");
	Serial.println("rms current");
	Serial.println(sqrt(rmsCurrent));
	Serial.println("dc current");
	Serial.println(dcCurrent);
	Serial.println("");*/
}

void TubeEffectAnalyser::handleHtDrivePushPullCurrentData(void * data)
{
	uint16_t dataReceived = *(uint16_t*)data;
	double floatingData = dataReceived;
	rmsCurrent = floatingData* floatingData*0.00001+ rmsCurrent*0.99999;
	dcCurrent = floatingData * 0.00001 + dcCurrent * 0.99999;
}
