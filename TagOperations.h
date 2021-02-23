#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <stdlib.h> 
#include <algorithm>
#include <cassert>

bool isMapIncCorrect(std::string&); // checks is tag is correct
bool isMapMltCorrect(std::string&);

bool isAggSumCorrect(std::string&);
bool isAggProCorrect(std::string&);
bool isAggAvgCorrect(std::string&);
bool isAggFstCorrect(std::string&);
bool isAggLstCorrect(std::string&);

bool isSrtRevCorrect(std::string&);
bool isSrtOrdAscCorrect(std::string&);
bool isSrtOrdDscCorrect(std::string&);
bool isSrtSlcCorrect(std::string&);
bool isSrtDstCorrect(std::string&);

std::vector<double>& mapInc(double, std::vector<double>&); // makes the appropriate calculations, which are diferent for each tag
std::vector<double>& mapMlt(double, std::vector<double>&);

double aggSum(std::vector<double>&);
double aggPro(std::vector<double>&);
double aggAvg(std::vector<double>&);
double aggFst(std::vector<double>&);
double aggLst(std::vector<double>&);

std::vector<double>& srtRev(std::vector<double>&);
std::vector<double>& srtOrd(std::string, std::vector<double>&);
std::vector<double> srtSlc(int, std::vector<double>&);
std::vector<double>& srtDst(std::vector<double>&);

double takeIncMltSlc(std::string&); // returns text between quotes depeding on the tag
std::string getOrder(std::string&);

bool isValidMap(std::string&); // validations for each tag group
bool isValidAgg(std::string&);
bool isValidSrt(std::string&);

bool isClosingMap(std::string&); // validation for closing tag group
bool isClosingAgg(std::string&);
bool isClosingSrt(std::string&);

bool isCorrect(std::string&); // checks if the string is one of the supported tags
bool isMissingDash(std::string&); // checks if it is supported, but without dash

bool hasValueDash(std::string&); // checks if it is a tag, which needs value
bool hasValueNoDash(std::string&); // checks if it needs value, but without dash

bool hasNoValue(std::string&); // checks if it is a tag with ot without a dash, which doesn't need value