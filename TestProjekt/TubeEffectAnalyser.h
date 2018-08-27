#pragma once
#include <stdlib.h>
#include <Arduino.h>
#include "Filter.h"
class TubeEffectAnalyser
{
public:
	TubeEffectAnalyser();
	~TubeEffectAnalyser();
	void analyseData();
	void handleHtDrivePushPullCurrentData(void * data);
private:
	double rmsCurrent;
	double dcCurrent;

};

