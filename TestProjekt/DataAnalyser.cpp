#include "DataAnalyser.h"
#include <stdlib.h>
#include <Arduino.h>


DataAnalyser::DataAnalyser(void(*errorHandler)(errorType))
{
	_errorHandler = errorHandler;
}

void DataAnalyser::iterateData(void* data, unsigned int channel)
{
	switch (channel)
	{
	case dataChannel::maFBan : 
		_flashAnalyser.handleMaFBanData(data);
		break;
	case dataChannel::maFBkat:
		_flashAnalyser.handleMaFBkatData(data);
		break;
	case dataChannel::htDrivePushPullCurrent:
		_tubeEffectAnalyser.handleHtDrivePushPullCurrentData(data);
		break;
	default:
		break;
	}
}

void DataAnalyser::analyseData()
{
	_flashAnalyser.analyseData();
	_tubeEffectAnalyser.analyseData();
}


DataAnalyser::~DataAnalyser()
{
}