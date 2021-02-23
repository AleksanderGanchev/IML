#include "ErrorList.h"

const std::string error0 = "There is no file in the appropriate format"; // Errors with files
const std::string error1 = "File is empty";
const std::string error2 = "File doesn't exist";
const std::string error100 = "Missing >"; // Errors for missing attributes
const std::string error101 = "Missing <";
const std::string error102 = "Missing tag content";
const std::string error103 = "Tag is missing attributes \"value\"";
const std::string error104 = "Missing -";
const std::string error105 = "There should be space between tag name and quotes";
const std::string error106 = "Missing \" \"";
const std::string error107 = "Missing \"";
const std::string error108 = "There is no value between the quotes";
const std::string error109 = "There are no angle brackets";
const std::string error110 = "There is not even one valid tag";
const std::string error200 = "There are extra spaces"; // Errors for extra attributes
const std::string error201 = "There are extra elements";
const std::string error202 = "There are extra spaces and elements";
const std::string error203 = "Opening tags are more than closing tags";
const std::string error204 = "Closing tags are more than opening tags";
const std::string error300 = "Agg closing tag is before opening tag"; // Errors with arrangement
const std::string error301 = "Map closing tag is before opening tag";
const std::string error302 = "Srt closing tag is before opening tag";
const std::string error400 = "Unknown tag used"; // Other errors
const std::string error401 = "Non-numeric value";
const std::string error402 = "The value between the quotes is only space";
const std::string error403 = "The value between the quotes is not a valid number";
const std::string error404 = "The value between \" \" must be \"ASC\" or \"DSC\"";
        
void ErrorList::setErrors(std::vector<std::string> &other)
{
	errors = other;
}

std::vector<std::string>& ErrorList::getErrors()
{
	return errors;
}


bool ErrorList::containsAngleBrackets(std::string &input)
{
	if (countOpening(input) == 0 && countClosing(input) == 0)
	{
		std::cout << "\n";
		errors.push_back(error109);
		print();
		return false;
	}

	return true;
}

bool ErrorList::areAngleBracketsEqual(std::string &input)
{
	if (countOpening(input) == countClosing(input))
	{
		return true;
	}
	else if (countOpening(input) > countClosing(input)) 
	{
		std::cout << "\n";
		errors.push_back(error100); 
		print();
	}
	else
	{
		std::cout << "\n";
		errors.push_back(error101);
		print();
	}

	return false;
}

bool ErrorList::containsValidAttribute(std::vector<std::string> &separated)
{
	size_t size = separated.size();

	for (size_t i = 0; i < size; i++)
	{
		if (isValidAgg(separated[i]) == true ||
			isValidMap(separated[i]) == true ||
			isValidSrt(separated[i]) == true ||
			isClosingAgg(separated[i]) == true ||
			isClosingMap(separated[i]) == true ||
			isClosingSrt(separated[i]) == true) // checks if string is valid opening or closing tag
		{
			return true;
		}
	}

	std::cout << "\n";
	errors.push_back(error110);
	print();

	return false;
}

bool ErrorList::areAttributesCorrect(std::vector<std::string> &separated)
{
	std::string tempSpaces = "";
	size_t size = separated.size(), tempSize = 0;
	bool flag = true;

	for (size_t i = 0; i < size; i++)
	{
		if (isValidAgg(separated[i]) == false &&
			isValidMap(separated[i]) == false &&
			isValidSrt(separated[i]) == false &&
			isClosingAgg(separated[i]) == false &&
			isClosingMap(separated[i]) == false &&
			isClosingSrt(separated[i]) == false &&
			isNumber(separated[i]) == false) // checks if the string is supported
		{
			if (flag == true)
			{
				std::cout << "\n";
			}
			inspectAttribute(separated[i]); // inspectes unsupported string for more detailed errors
			
			tempSize = 51 - separated[i].size(); // number of spaces to create box
			tempSpaces = "";
			flag = false;

			while (tempSize != 0)
			{
				tempSpaces += " ";
				tempSize--;
			}

			std::cout << "   +--------------------------------------------------------+" << std::endl;
			std::cout << "   |>>" << separated[i] << "<<" << tempSpaces << " |" << std::endl;

			print();
			empty();
		}
	}
	return flag;
}

bool ErrorList::areAggClosingMore(size_t &aggOpen, size_t &aggClose, size_t &aggBefore)
{
	if (aggOpen < aggClose && aggBefore == 0)
	{
		std::cout << "\n";
		aggBefore++;
		errors.push_back(error300);
		print();
		return true;
	}

	return false;
}

bool ErrorList::areMapClosingMore(size_t &mapOpen, size_t &mapClose, size_t &mapBefore)
{
	if (mapOpen < mapClose && mapBefore == 0)
	{
		std::cout << "\n";
		mapBefore++;
		errors.push_back(error301);
		print();
		return true;
	}

	return false;
}

bool ErrorList::areSrtClosingMore(size_t &srtOpen, size_t &srtClose, size_t &srtBefore)
{
	if (srtOpen < srtClose && srtBefore == 0)
	{
		std::cout << "\n";
		srtBefore++;
		errors.push_back(error302);
		print();
		return true;
	}

	return false;
}

bool ErrorList::checkOpeningClosingTags(std::vector<std::string> &content)
{
	size_t size = content.size();
	size_t aggOpen = 0, aggClose = 0, mapOpen = 0, mapClose = 0, srtOpen = 0, srtClose = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (isValidAgg(content[i]))
		{
			aggOpen++;
		}
		else if (isValidMap(content[i]))
		{
			mapOpen++;
		}
		else if (isValidSrt(content[i]))
		{
			srtOpen++;
		}
		else if (isClosingAgg(content[i]))
		{
			aggClose++;
		}
		else if (isClosingMap(content[i]))
		{
			mapClose++;
		}
		else if (isClosingSrt(content[i]))
		{
			srtClose++;
		}
	}

	if (aggOpen + mapOpen + srtOpen == aggClose + mapClose + srtClose)
	{
		return true;
	}
	else if (aggOpen + mapOpen + srtOpen > aggClose + mapClose + srtClose)
	{
		errors.push_back(error203);
	}
	else
	{
		errors.push_back(error204);
	}

	std::cout << "\n";
	print();
	return false;
}

bool ErrorList::checkTagSequence(std::vector<std::string> &content)
{
	size_t size = content.size();
	size_t aggOpen = 0, aggClose = 0, mapOpen = 0, mapClose = 0, srtOpen = 0, srtClose = 0, aggBefore = 0, mapBefore = 0, srtBefore = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (isValidAgg(content[i]))
		{
			aggOpen++;
		}
		else if (isValidMap(content[i]))
		{
			mapOpen++;
		}
		else if (isValidSrt(content[i]))
		{
			srtOpen++;
		}
		else if (isClosingAgg(content[i]))
		{
			aggClose++;
		}
		else if (isClosingMap(content[i]))
		{
			mapClose++;
		}
		else if (isClosingSrt(content[i]))
		{
			srtClose++;
		}

		if (areAggClosingMore(aggOpen, aggClose, aggBefore) || areMapClosingMore(mapOpen, mapClose, mapBefore) || areSrtClosingMore(srtOpen, srtClose, srtBefore))
		{
			return false;
		}
	}

	return true;
}

void ErrorList::print()
{
	std::string tempSpaces = "";
	size_t size = errors.size(), tempSize = 0;

	std::cout << "   +--------------------------------------------------------+" << std::endl;
	std::cout << "   |                       ERROR LIST                       |" << std::endl;
	std::cout << "   +--------------------------------------------------------+" << std::endl;

	for (size_t i = 0; i < size; i++)
	{
		tempSize = 51 - errors[i].size(); // calculates number of spaces
		tempSpaces = "";

		while (tempSize != 0)
		{
			tempSpaces += " ";
			tempSize--;
		}
		std::cout << "   | " << i + 1 << ") " << errors[i]  << tempSpaces << " |" << std::endl;
	}
	std::cout << "   +--------------------------------------------------------+\n" << std::endl;
}

void ErrorList::empty() // empties vector
{
	while (!(errors.empty()))
	{
		errors.pop_back();
	}
}

bool ErrorList::missingQuotesAndValue(std::vector<std::string> &content, size_t &size)
{
	if (size == 1 || (size == 2 && content[1] == ""))
	{
		errors.push_back(error103);
		return true;
	}

	return false;
}

bool ErrorList::spacesBetweenQuotes(std::vector<std::string> &content, size_t &size)
{
	if (size > 3 && returnNumberSpaces(content) > 1 && returnNumberQuotes(content) == 2 && size - returnNumberSpaces(content) == 3 && containsTwoQuotes(content))
	{
		errors.push_back(error402);
		return true;
	}

	return false;
}

bool ErrorList::missingDash(std::vector<std::string> &content, size_t &size) 
{
	if (isMissingDash(content[0])) // valid tag, but missing dash
	{
		errors.push_back(error104);

		if (size == 1)
		{
			errors.push_back(error103);
			return true;
		}
		if (hasValueNoDash(content[0]) && (missingQuotesAndValue(content, size) || spacesBetweenQuotes(content, size)))
		{ // check if the current tag need value and is missing quotes and value or there is only space between the quotes
			return true;
		}
	}

	return false;
}

bool ErrorList::extraSpacesElements(std::vector<std::string> &content, size_t &size)
{
	if (containsNoValueTag(content) && size > 1)
	{
		if (returnNumberSpaces(content) > 0 && size - returnNumberSpaces(content) == 1) // checks for extra spaces
		{
			errors.push_back(error200);
		}
		else if (returnNumberSpaces(content) == 0) // checks for extra elements
		{
			errors.push_back(error201);
		}
		else // both
		{
			errors.push_back(error202);
		}

		return true;
	}

	return false;
}

bool ErrorList::lastStringSize(std::vector<std::string> &content, std::string &lastText)
{
	if (lastText.size() == 0) // no value between the quotes
	{
		errors.push_back(error108);
	}
	else
	{
		lastText = removeQuotes(lastText); // removes the quotes from the last string

		if (lastText.size() == 0) // proverka sled kaot sme mahnali quote
		{
			errors.push_back(error108);
			return true;
		}

		if (!isNumber(lastText) && !(content[0] == "SRT-ORD" || content[0] == "SRTORD" || content[0][4] == 'O' || content[0][3] == 'O'))
		{ // checks if the last string is different than number and if the tag doesn't number
			errors.push_back(error403);
		}
		else if ((content[0] == "SRT-ORD" || content[0] == "SRTORD") && lastText != "ASC" && lastText != "DSC")
		{ 
			errors.push_back(error404);
		}
	}

	return false;
}


void ErrorList::oneQuote(std::vector<std::string> &content, size_t &size)
{
	errors.push_back(error107);

	std::string lastText = returnLastString(content);
	std::string withoutQuotes = removeQuotes(lastText);

	if (!isNumber(withoutQuotes))
	{
		errors.push_back(error401);
	}
}

void ErrorList::noQuotes(std::vector<std::string> &content, size_t &size)
{
	if (!containsQuotes(content))
	{
		errors.push_back(error106);
		std::string temp = returnLastString(content);

		if (!isNumber(temp)) // checks if the last string is number
		{
			errors.push_back(error401);
		}
	}
}

void ErrorList::noSpaceBetween(std::vector<std::string> &content, size_t &size)
{
	if (returnNumberSpaces(content) == 0)
	{
		if (size >= 3 && content[1] != "")
		{
			errors.push_back(error201);
		}
		else
		{
			errors.push_back(error105);
		}
	}
	else if (size - returnNumberSpaces(content) <= 3 && returnNumberSpaces(content) <= 1)
	{
		errors.push_back(error201);
	}
}

bool ErrorList::sizeBiggerThanTwo(std::vector<std::string> &content, size_t &size)
{
	if (size >= 2)
	{
		if (content[1] != "")
		{
			noSpaceBetween(content, size);
		}

		if (content[size - 1][0] != '"' || content[size - 1][content[size - 1].size() - 1] != '"')
		{ // checks if the first or last symbol of the last vector element is different from quotes
			if (content[size - 1][0] != '"' && (content[size - 1].size() == 0 || content[size - 1][content[size - 1].size() - 1] != '"'))
			{
				noQuotes(content, size);
			}
			else if (returnNumberQuotes(content) < 2)
			{
				oneQuote(content, size);
			}
		}
		else
		{
			std::string lastText = returnLastString(content);

			if (lastStringSize(content, lastText))
			{
				return true;
			}
		}
	}

	return false;
}

void ErrorList::wrongSize(std::vector<std::string> &content, size_t &size)
{
	if (returnNumberSpaces(content) > 1 && size - returnNumberSpaces(content) == 2) // checks for extra spaces
	{
		errors.push_back(error200);
	}
	else if (size - returnNumberSpaces(content) <= 3 && returnNumberSpaces(content) <= 1)
	{
		if ((content[content.size() - 1][0] != '"' || content[content.size() - 1][content[content.size() - 1].size() - 1] != '"')
			&& (content[content.size() - 1][0] == '"' || content[content.size() - 1][content[content.size() - 1].size() - 1] == '"'))
		{ // checks if at either the first or last element in the last string is quotes
			errors.push_back(error403);
		}
		else
		{
			errors.push_back(error201);
		}
	}
	else
	{
		errors.push_back(error202);
	}
}

void ErrorList::inspectAttribute(std::string &input)
{
	std::vector<std::string> content;
	splitError(content, input);

	assert(content.size() != 0);

	if (isVectorSpaces(content))
	{
		errors.push_back(error102);
		return;
	}

	if (containsUnknownTag(content))
	{
		errors.push_back(error400);
		return;
	}

	size_t size = content.size();
	
	if ((hasValueDash(content[0]) && (missingQuotesAndValue(content, size) || spacesBetweenQuotes(content, size)))
		|| missingDash(content, size)
		|| extraSpacesElements(content, size)) // cases if the value is valid and has dash and is missing quotes with value or quotes with space
	{                                          // or if it is a valid tag without dash, or if it has extra element, spaces or both
		return;
	}
	
	if (size > 3) 
	{
		wrongSize(content, size);
	}

	if (sizeBiggerThanTwo(content, size)) 
	{
		return;
	}
}

bool ErrorList::fileValidation(std::ifstream &fileName)
{
	if (fileName.fail() )
	{
		std::cout << "\n";
		errors.push_back(error0);
		print();
		return false;
	}
	else if (fileName.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\n";
		errors.push_back(error1);
		print();
		return false;
	}

	return true;
}

bool ErrorList::scanForErrors(std::string &input)
{
	if (areAngleBracketsEqual(input) && containsAngleBrackets(input))
	{
		std::vector<std::string> separated = separateText(input);

		if (areAttributesCorrect(separated) && containsValidAttribute(separated))
		{
			if (checkOpeningClosingTags(separated))
			{
				return checkTagSequence(separated);
			}
		}
	}

	return false;
}

void ErrorList::saveResult(std::ifstream &outputFile, std::string &fileName, std::string &output)
{
	if (outputFile.fail())
	{
		std::cout << "\n";
		errors.push_back(error2);
		print();

		std::string userChoice;
		std::cout << "Enter 'Y' to create a file, otherwise the result will be printed on the console: ";
		std::cin >> userChoice;

		if (userChoice == "Y")
		{
			std::ofstream file(fileName);
			file << output;
			file.close();
			std::cout << "\nSTATUS: " << fileName << " was successfully created and result was saved!" << std::endl;
		}
		else
		{
			std::cout << "\nSTATUS: You chose to print the result on the console!" << std::endl;
			std::cout << "RESULT: " << output << std::endl;
		}

	}
	else if (outputFile.is_open())
	{
		std::ofstream file(fileName);
		file << output;
		file.close();
		std::cout << "STATUS: " << "Result was successfully saved in " << fileName << "!" << std::endl;
	}
	else
	{
		assert(false);
	}
}
