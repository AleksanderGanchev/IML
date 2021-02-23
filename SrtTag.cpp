#include "SrtTag.h"

SrtTag::SrtTag(std::string _name, std::vector<double> _content, std::string _id)
{
	this->name = _name;
	this->content = _content;
	this->id = _id;
}

void SrtTag::addToContent(double &number)
{
	this->content.push_back(number);
}

void SrtTag::reverseContent()
{
	reverseVector(this->content);
}

void SrtTag::printInformation()
{
	std::cout << "(Tag Name: " << this->name << " Content:";

	printVector(this->content);

	std::cout << " )";
}

std::string& SrtTag::returnName()
{
	return this->name;
}

std::vector<double>& SrtTag::returnContent()
{
	return this->content;
}

std::string& SrtTag::returnId()
{
	return this->id;
}

std::vector<double> SrtTag::calculateNode(std::vector<double> &containerForContent)
{
	std::vector<double> result;

	if (isSrtRevCorrect(this->name))
	{
		result = srtRev(containerForContent);
	}
	else if (isSrtOrdAscCorrect(this->name))
	{
		result = srtOrd(getOrder(this->name), containerForContent);
	}
	else if (isSrtOrdDscCorrect(this->name))
	{
		result = srtSlc((double)takeIncMltSlc(this->name), containerForContent);
	}
	else if (isSrtSlcCorrect(this->name))
	{
		result = srtSlc((double)takeIncMltSlc(this->name), containerForContent);
	}
	else 
	{
		assert(isSrtDstCorrect(this->name));
		std::vector<double> reversedVector = returnReversedVector(containerForContent);
		result = srtDst(reversedVector);

		reverseVector(result);
	}

	return result;
}
