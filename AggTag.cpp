#include "AggTag.h"

AggTag::AggTag(std::string _name, std::vector<double> _content, std::string _id)
{
	this->name = _name;
	this->content = _content;
	this->id = _id;
}

void AggTag::addToContent(double &number)
{
	this->content.push_back(number);
}

void AggTag::reverseContent()
{
	reverseVector(this->content);
}

void AggTag::printInformation()
{
	std::cout << "(Tag Name: " << this->name << " Content:";

	printVector(this->content);

	std::cout << " )";
}

std::string& AggTag::returnName()
{
	return this->name;
}

std::vector<double>& AggTag::returnContent()
{
	return this->content;
}

std::string& AggTag::returnId()
{
	return this->id;
}

std::vector<double> AggTag::calculateNode(std::vector<double> &containerForContent)
{
	std::vector<double> nodeResult;

	if (isAggSumCorrect(this->name))
	{
		nodeResult.push_back(aggSum(containerForContent));
	}
	else if (isAggProCorrect(this->name))
	{
		nodeResult.push_back(aggPro(containerForContent));
	}
	else if (isAggAvgCorrect(this->name))
	{
		nodeResult.push_back(aggAvg(containerForContent));
	}
	else if (isAggFstCorrect(this->name))
	{
		nodeResult.push_back(aggFst(containerForContent));
	}
	else
	{
		assert(isAggLstCorrect(this->name)); // assert, because this is the last option
		nodeResult.push_back(aggLst(srtRev(containerForContent)));
	}

	return nodeResult;
}
