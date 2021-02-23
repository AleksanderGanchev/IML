#include "MapTag.h"

MapTag::MapTag(std::string _name, std::vector<double> _content, std::string _id)
{
	this->name = _name;
	this->content = _content;
	this->id = _id;
}

void MapTag::addToContent(double &number)
{
	this->content.push_back(number);
}

void MapTag::reverseContent()
{
	reverseVector(this->content);
}

void MapTag::printInformation()
{
	std::cout << "(Tag Name: " << this->name << " Content:";

	printVector(this->content);

	std::cout << " )";
}

std::string& MapTag::returnName()
{
	return this->name;
}

std::vector<double>& MapTag::returnContent()
{
	return this->content;
}

std::string& MapTag::returnId()
{
	return this->id;
}

std::vector<double> MapTag::calculateNode(std::vector<double> &containerForContent)
{
	std::vector<double> nodeResult;

	if (isMapIncCorrect(this->name))
	{
		double toAdd = takeIncMltSlc(this->name);
		nodeResult = mapInc(toAdd, containerForContent);
	}
	else
	{
		assert(isMapMltCorrect(this->name));

		double toMultiply = takeIncMltSlc(this->name);
		nodeResult = mapMlt(toMultiply, containerForContent);
	}

	return nodeResult;
}
