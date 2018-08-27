#pragma once
#include "CircularBuffer.h"

class Filter
{
public:
	Filter();
	Filter(std::vector<float> &aParameters, std::vector<float> &bParameters);
	void setAParameters(std::vector<float> &aParameters);
	void setBParameters(std::vector<float> &bParameters);
	float iterate();
	void setInputBuffer(CircularBuffer<float>& inputBuffer);

	~Filter();
private:
	std::vector<float> *_aParameters;
	std::vector<float> *_bParameters;
	CircularBuffer<float> *_input;
	CircularBuffer<float> *_output;

};

