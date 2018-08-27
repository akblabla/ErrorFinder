#include "Filter.h"

Filter::Filter()
{
}

Filter::Filter(std::vector<float> &aParameters, std::vector<float> &bParameters)// : _input(bParameters.size()), _output(aParameters.size())
{
	for (unsigned int i = 0; i < aParameters.size(); i++) {
		_aParameters->push_back(aParameters.at(i));
	}
	for (unsigned int i = 0; i < bParameters.size(); i++) {
		_bParameters->push_back(bParameters.at(i));
	}
}

void Filter::setAParameters(std::vector<float> &aParameters)
{
	_aParameters->clear();
	for (unsigned int i = 0; i < aParameters.size(); i++) {
		_aParameters->push_back(aParameters.at(i));
	}
	_output->setCapacity(_aParameters->size());
}

void Filter::setBParameters(std::vector<float> &bParameters)
{
	_bParameters->clear();
	for (unsigned int i = 0; i < bParameters.size(); i++) {
		_bParameters->push_back(bParameters.at(i));
	}
	//_output.setSize(_bParameters.size());
}

float Filter::iterate()
{
	float result = 0;
	for (unsigned int i = 0; i < _bParameters->size(); i++) {
		result += _input->read(i)*_bParameters->at(i);
	}
	for (unsigned int i = 0; i < _aParameters->size(); i++) {
		result += _output->read(i)*_aParameters->at(i);
	}
	_output->push(result);
	return result;
}

void Filter::setInputBuffer(CircularBuffer<float>& inputBuffer)
{
	_input = &inputBuffer;
}

Filter::~Filter()
{
	delete(_aParameters);
	delete(_bParameters);
	delete(_output);
}
