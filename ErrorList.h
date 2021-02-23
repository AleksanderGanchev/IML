#pragma once
#include "TextManipulation.h"
#include "TagOperations.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>

class ErrorList
{
private:
	std::vector<std::string> errors;

public:
	void setErrors(std::vector<std::string>&);
	std::vector<std::string>& getErrors();

	bool containsAngleBrackets(std::string&); // checks if string contains opening or closing brackets
	bool areAngleBracketsEqual(std::string&); // checks if the number of opening brackets is equal to the number of closing

	bool containsValidAttribute(std::vector<std::string>&); // checks if the vector contains even one valid tag
	bool areAttributesCorrect(std::vector<std::string>&); // checks if vector elements are correct tag or a number

	bool areAggClosingMore(size_t&, size_t&, size_t&); // validations if closing tags are more
	bool areMapClosingMore(size_t&, size_t&, size_t&);
	bool areSrtClosingMore(size_t&, size_t&, size_t&);

	bool checkOpeningClosingTags(std::vector<std::string>&); // checks opening closing tags ratio
	bool checkTagSequence(std::vector<std::string>&); // checks in what order are tags written

	void print(); // prints error list
	void empty(); // empties vector of errors

	bool missingQuotesAndValue(std::vector<std::string>&, size_t&); // checks for missing quotes and value between them
	bool spacesBetweenQuotes(std::vector<std::string>&, size_t&); // check if the value berween the quotes is only spaces
	bool missingDash(std::vector<std::string>&, size_t&); // checks if tag is valid, but without dash
	bool extraSpacesElements(std::vector<std::string>&, size_t&); // checks for extra spaces, elements or both
	bool lastStringSize(std::vector<std::string>&, std::string&); // checks cases concerning the size of the last string

	void oneQuote(std::vector<std::string>&, size_t&); // errors for one missing quote
	void noQuotes(std::vector<std::string>&, size_t&); // errors if the vector doesn't contain quotes
	void noSpaceBetween(std::vector<std::string>&, size_t&); // errors for missing space and extra elements

	bool sizeBiggerThanTwo(std::vector<std::string>&, size_t&); // errors for vector, whose size is bigger than two
	
	void wrongSize(std::vector<std::string>&, size_t&); // checks for errors if vector is size is bigger than 3
	void inspectAttribute(std::string&); // series of checks to identify the error in invalid string

	bool fileValidation(std::ifstream&); // checks if file is appropriate format or empty
	bool scanForErrors(std::string&); // series of check for errors on different levels

	void saveResult(std::ifstream&, std::string&, std::string&); // checks for errors with saving the result in file
};

