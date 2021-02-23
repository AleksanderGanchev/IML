#pragma once
#include "TagOperations.h"
#include "TextManipulation.h"

class Tag
{
public:
	virtual void addToContent(double&) = 0; // adds a number to tag's content
	virtual void reverseContent() = 0; // reverse tag's content
	virtual void printInformation() = 0; // prints tag's name and content

	virtual std::string& returnName() = 0; // returns tag's name
	virtual std::vector<double>& returnContent() = 0; // returns tag's content
	virtual std::string& returnId() = 0; // returns tag's id

	virtual std::vector<double> calculateNode(std::vector<double>&) = 0; // calculate tag's result
};

