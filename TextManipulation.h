#pragma once
#include "TagOperations.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

inline void reverseVector(std::vector<double> &list) // reverses vector 
{
	std::vector<double> tempVector;

	while (!(list.empty()))
	{
		tempVector.push_back(list.back());
		list.pop_back();
	}

	list = tempVector;
}
inline std::vector<double> returnReversedVector(std::vector<double> &list) // return reversed vector
{
	reverseVector(list);
	std::vector<double> tempVector = list;
	reverseVector(list);

	return tempVector;
}

inline void printVector(std::vector<double> content) // prints vector's content from the last element to the first
{
	while (!content.empty())
	{
		std::cout << content.back() << " ";
		content.pop_back();
	}
}
inline void printVectorFront(std::vector<std::string> &content) // prints vector from the first element to the last
{
	size_t size = content.size();

	for (size_t i = 0; i < size; i++)
	{
		std::cout << content[i] << std::endl;
	}
}  

inline void emptyVector(std::vector<double> &content) // empties vector
{
	while (!(content.empty()))
	{
		content.pop_back();
	}
}
inline void returnContent(std::istream &file, std::string &output) // reads text from file and returns it on one line
{
	std::string temp;

	while (getline(file, temp))
	{
		if (temp == "K\n")
		{
			break;
		}

		output += temp;
	}
}

inline size_t countOpening(std::string &input) // counts opening tags
{
	size_t size = input.size(), counterOpening = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (input[i] == '<')
		{
			counterOpening++;
		}
	}

	return counterOpening;
}
inline size_t countClosing(std::string &input) // counts closing tags
{
	size_t size = input.size(), counterClosing = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (input[i] == '>')
		{
			counterClosing++;
		}
	}

	return counterClosing;
}

inline void addNumber(std::vector<std::string> &separated, std::string &input, size_t &counter) // reads text and returns number as a string to the vector
{
	std::string temp;
	while (input[counter] != '<' && input[counter] != ' ')
	{
		temp += input[counter];
		counter++;
	}

	separated.push_back(temp);
}
inline void addTag(std::vector<std::string> &separated, std::string &input, size_t &counter) // adds tag name to vector
{
	std::string temp;
	counter++;

	while (input[counter] != '>')
	{
		temp += input[counter];
		counter++;
	}

	separated.push_back(temp);
}
inline void addLetters(std::vector<std::string> &separated, std::string &input, size_t &counter) // adds letters, which are not in the tag
{
	std::string temp;

	while (input[counter] != '<' && input[counter] != ' ')
	{
		temp += input[counter];
		counter++;
	}

	counter--;
	separated.push_back(temp);
}

inline std::vector<std::string> separateText(std::string &input) // return text separated to inspect it line by line
{
	std::vector<std::string> separated;
	size_t size = input.size();

	for (size_t i = 0; i < size; i++)
	{
		if (input[i] == '-' || isdigit(input[i]) == 4)
		{
			addNumber(separated, input, i); // adds number
		}
		if (input[i] == '<')
		{
			addTag(separated, input, i); // adds tag
		}
		if (isalpha(input[i]))
		{
			addLetters(separated, input, i); // adds letters that dont't in tag
		}
	}

	return separated;
}

inline bool isNumber(std::string &input) // checks if a string is number
{
	auto result = double();
	auto i = std::istringstream(input);

	i >> result;

	return !i.fail() && i.eof();
}

inline bool containsUnknownTag(std::vector<std::string> &content) // checks if vector contains unsupported tag
{
	size_t size = content.size();

	for (size_t i = 0; i < size; i++)
	{
		if (isCorrect(content[i]) || isMissingDash(content[i]))
		{
			return false;
		}
	}

	return true;
}
inline bool containsNoValueTag(std::vector<std::string> &content) // contains tag that doesn't need value
{
	size_t size = content.size();

	for (size_t i = 0; i < size; i++)
	{
		if (hasNoValue(content[i]))
		{
			return true;
		}
	}

	return false;
}

inline bool containsTwoQuotes(std::vector<std::string> &content) // checks if two of the strings in the vector are quotes
{
	size_t size = content.size(), counter = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (content[i] == "\"")
		{
			counter++;
		}
		if (content[i] == "\"" && i != 0)
		{
			counter++;
			break;
		}
	}

	return counter == 2;
}
inline bool containsQuotes(std::vector<std::string> &content) // checks every element of the vector for a quotes
{
	for (size_t i = 0; i < content.size(); i++)
	{
		if (content[i][0] == '"')
		{
			for (size_t j = 1; j < content[i].size(); j++)
			{
				if (content[i][j] == '"')
				{
					return true;
				}
			}
		}
	}

	return false;
}
inline bool containsSpace(std::string &input) // checks if string contains space
{
	size_t size = input.size();

	for (size_t i = 0; i < size; i++)
	{
		if (input[i] == ' ')
		{
			return true;
		}
	}
	return false;
}
inline bool containsQuotesAndSpace(std::string &input) // checks if string contains quotes and space
{
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] != ' ' && input[i] != '"')
		{
			return false;
		}
		if (input[i] == '"' && containsSpace(input))
		{
			return true;
		}
	}
	return false;
}

inline bool isVectorSpaces(std::vector<std::string> content) // checks if every element of the vector is a space
{
	for (size_t i = 0; i < content.size(); i++)
	{
		if (content[i] != "")
		{
			return false;
		}
	}

	return true;
}
inline bool isStringSpaces(std::string &input) // checks if every element of the string is space
{
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] != ' ')
		{
			return false;
		}
	}

	return true;
}

inline void addOtherThanSpace(std::vector<std::string> &content, std::string &temp, std::string &input, size_t &size, size_t &counter) // adds symbols different from letters or quotes
{
	while (counter < size && input[counter] != '"' && !isalpha(input[counter]))
	{
		if (input[counter] == ' ') // checks if a symbol is space
		{
			content.push_back(temp);
			temp = "";
			break;
		}

		temp += input[counter];
		counter++;
	}
}
inline void addLowerCase(std::vector<std::string> &content, std::string &temp, std::string &input, size_t &i) // adds lower case letter
{
	if (islower(input[i]))
	{
		content.push_back(temp);
		temp = "";
	}
	temp += input[i];
}

inline void splitError(std::vector<std::string> &content, std::string &input) // splittes string with error to vector
{
	std::string temp;
	size_t size = input.size();

	for (size_t i = 0; i < size; i++)
	{
		if (input[i] == ' ' || input[i] == '"' || isdigit(input[i]) == 4)
		{
			if (input[i] == ' ')
			{
				content.push_back(temp);
				temp = "";
			}
			else
			{
				if (i != 0)
				{
					content.push_back(temp);
				}
				temp = input[i];
				i++;

				addOtherThanSpace(content, temp, input, size, i); // catch case in the current symbol is not space, but adds it if it isnide the method
				temp += input[i];
			}
		}
		else
		{
			addLowerCase(content, temp, input, i);
		}
	}

	content.push_back(temp);
}

inline size_t returnNumberSpaces(std::vector<std::string> content) // return number of string, which are only spaces in the vector
{
	size_t br = 0;

	for (size_t i = 0; i < content.size(); i++)
	{
		if (isStringSpaces(content[i]))
		{
			br++;
		}
	}

	return br;
}
inline size_t returnNumberQuotes(std::vector<std::string> &content) // returns number of quotes
{
	size_t counter = 0;

	for (size_t i = 0; i < content.size(); i++)
	{
		for (size_t j = 0; j < content[i].size(); j++)
		{
			if (content[i][j] == '\"')
			{
				counter++;
			}
		}
	}

	return counter;
}

inline std::string returnLastString(std::vector<std::string> &content) // returns the last string which is not full 
{                                                                       //of spaces and doesn't contains spaces and quotes at the same time
	std::string temp;
	size_t size = content.size();
		
	for (size_t i = 0; i < size; i++)
	{
		if (!isStringSpaces(content[i]) && !containsQuotesAndSpace(content[i]))
		{
			temp = content[i];
		}
	}

	return temp;
}
inline std::string removeQuotes(std::string &input) // removes quotes from string
{
	size_t size = input.size();
	std::string temp;

	for (size_t i = 0; i < size; i++)
	{
		if (input[i] != '"')
		{
			temp += input[i];
		}
	}

	return temp;
}

inline std::string convertToString(std::vector<double> &content) // converts vector to string
{
	std::vector<double> newVector = returnReversedVector(content);
	std::stringstream output;
	std::copy(newVector.begin(), newVector.end(), std::ostream_iterator<double>(output, " "));

	return output.str();
}