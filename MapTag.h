#pragma once
#include "Tag.h"

class MapTag : public Tag
{
public:
	MapTag(std::string, std::vector<double>, std::string);

	void addToContent(double&) override;
	void reverseContent() override;
	void printInformation() override;

	std::string& returnName() override;
	std::vector<double>& returnContent() override;
	std::string& returnId() override;

	std::vector<double> calculateNode(std::vector<double>&) override;

private:
	std::string name;
	std::vector<double> content;
	std::string id;

};

