#pragma once
#include "ErrorType.h"
#include "FlashAnalyser.h"
#include "TubeEffectAnalyser.h"
enum dataChannel { maFBan = 14, maFBkat = 15, htDrivePushPullCurrent = 16};
class DataAnalyser
{
public:
	DataAnalyser(void(*errorHandler)(errorType));
	void iterateData(void* data, unsigned int channel);
	void analyseData();
	~DataAnalyser();
	float _output;
private:

	void(*_errorHandler)(errorType);
	FlashAnalyser _flashAnalyser;
	TubeEffectAnalyser _tubeEffectAnalyser;
};

