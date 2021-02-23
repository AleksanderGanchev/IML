#include "TagOperations.h"

bool isMapIncCorrect(std::string &toCheck)
{
	std::regex inc("(<MAP-INC) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");

	if (regex_match(toCheck, inc))
	{
		return true;
	}

	return false;
}

bool isMapMltCorrect(std::string &toCheck)
{
	std::regex mlt("(<MAP-MLT) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");

	if (regex_match(toCheck, mlt))
	{
		return true;
	}

	return false;
}

bool isAggSumCorrect(std::string &toCheck)
{
	std::regex sum("(<AGG-SUM>)");

	if (regex_match(toCheck, sum))
	{
		return true;
	}

	return false;
}

bool isAggProCorrect(std::string &toCheck)
{
	std::regex pro("(<AGG-PRO>)");

	if (regex_match(toCheck, pro))
	{
		return true;
	}

	return false;
}

bool isAggAvgCorrect(std::string &toCheck)
{
	std::regex avg("(<AGG-AVG>)");

	if (regex_match(toCheck, avg))
	{
		return true;
	}

	return false;
}

bool isAggFstCorrect(std::string &toCheck)
{
	std::regex fst("(<AGG-FST>)");

	if (regex_match(toCheck, fst))
	{
		return true;
	}

	return false;
}

bool isAggLstCorrect(std::string &toCheck)
{
	std::regex lst("(<AGG-LST>)");

	if (regex_match(toCheck, lst))
	{
		return true;
	}

	return false;
}

bool isSrtRevCorrect(std::string &toCheck)
{
	std::regex rev("(<SRT-REV>)");

	if (regex_match(toCheck, rev))
	{
		return true;
	}

	return false;
}

bool isSrtOrdAscCorrect(std::string &toCheck)
{
	std::regex asc("(<SRT-ORD) (\")(ASC)(\">)");

	if (regex_match(toCheck, asc))
	{
		return true;
	}

	return false;
}

bool isSrtOrdDscCorrect(std::string &toCheck)
{
	std::regex dsc("(<SRT-ORD) (\")(DSC)(\">)");

	if (regex_match(toCheck, dsc))
	{
		return true;
	}

	return false;
}

bool isSrtSlcCorrect(std::string &toCheck)
{
	std::regex slc("(<SRT-SLC) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");

	if (regex_match(toCheck, slc))
	{
		return true;
	}

	return false;
}

bool isSrtDstCorrect(std::string &toCheck)
{
	std::regex dst("(<SRT-DST>)");

	if (regex_match(toCheck, dst))
	{
		return true;
	}

	return false;
}

std::vector<double>& mapInc(double toAdd, std::vector<double> &content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		content[i] += toAdd;
	}

	return content;
}

std::vector<double>& mapMlt(double toMultiply, std::vector<double> &content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		content[i] *= toMultiply;
	}

	return content;
}

double aggSum(std::vector<double> &content)
{
	double sum = 0;

	for (size_t i = 0; i < content.size(); i++)
	{
		sum += content[i];
	}

	return sum;
}

double aggPro(std::vector<double> &content)
{
	double product = 1;

	for (size_t i = 0; i < content.size(); i++)
	{
		product *= content[i];
	}

	return product;
}

double aggAvg(std::vector<double> &content)
{
	double sum = 0;

	for (size_t i = 0; i < content.size(); i++)
	{
		sum += content[i];
	}

	return (sum / content.size());
}

double aggFst(std::vector<double> &content)
{
	return content[0];
}

double aggLst(std::vector<double>& content)
{
	return content[content.size() - 1];
}

std::vector<double>& srtRev(std::vector<double> &content)
{
	std::reverse(content.begin(), content.end());

	return content;
}

std::vector<double>& srtOrd(std::string order, std::vector<double> &content)
{
	if (order == "ASC")
	{
		sort(content.begin(), content.end());
	}
	else
	{
		assert(order == "DSC");
		sort(content.begin(), content.end(), std::greater<int>());
	}

	return content;
}

std::vector<double> srtSlc(int begining, std::vector<double> &content)
{
	std::vector<double> tempVector;

	for (size_t i = begining; i < content.size(); i++)
	{
		tempVector.push_back(content[i]);
	}

	return tempVector;
}

std::vector<double>& srtDst(std::vector<double>& content)
{
	auto end = content.end();

	for (auto it = content.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	content.erase(end, content.end());

	return content;
}

double takeIncMltSlc(std::string &input)
{
	std::string temp;
	size_t i = 10;

	while (input[i] != '\"')
	{
		temp += input[i];
		i++;
	}

	return atof(temp.c_str());
}

std::string getOrder(std::string &input)
{
	std::string temp;
	size_t index = 10;

	while (input[index] != '\"')
	{
		temp += input[index];
		index++;
	}

	return temp;
}

bool isValidMap(std::string &tag)
{
	std::regex inc("(MAP-INC) ((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	std::regex mlt("(MAP-MLT) ((\"(-?(\\d)+(\\.)?(\\d)*)\"))");

	return (std::regex_match(tag, inc) || std::regex_match(tag, mlt)) ? true : false;
}

bool isValidAgg(std::string &tag)
{

	std::regex sum("(AGG-SUM)");
	std::regex pro("(AGG-PRO)");
	std::regex avg("(AGG-AVG)");
	std::regex fst("(AGG-FST)");
	std::regex lst("(AGG-LST)");
	return (std::regex_match(tag, sum)
		|| std::regex_match(tag, pro)
		|| std::regex_match(tag, avg)
		|| std::regex_match(tag, fst)
		|| std::regex_match(tag, lst)) ? true : false;
}

bool isValidSrt(std::string &tag)
{
	std::regex rev("(SRT-REV)");
	std::regex asc("(SRT-ORD) (\")(ASC)(\")");
	std::regex dsc("(SRT-ORD) (\")(DSC)(\")");
	std::regex dst("(SRT-DST)");
	std::regex slc("(SRT-SLC) ((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	return  (regex_match(tag, asc) ||
		regex_match(tag, dsc) ||
		regex_match(tag, slc) ||
		regex_match(tag, dst) ||
		regex_match(tag, rev))
		? true : false;
}

bool isClosingMap(std::string &tag)
{
	return tag == "/MAP-INC" || tag == "/MAP-MLT";
}

bool isClosingAgg(std::string &tag)
{
	return tag == "/AGG-SUM" || tag == "/AGG-PRO"
		|| tag == "/AGG-AVG" || tag == "/AGG-FST"
		|| tag == "/AGG-LST";
}

bool isClosingSrt(std::string &tag)
{
	return tag == "/SRT-REV" || tag == "/SRT-ORD"
		|| tag == "/SRT-SLC" || tag == "/SRT-DST";
}

bool isCorrect(std::string &input)
{
	return input == "MAP-INC" || input == "MAP-MLT" ||
		input == "AGG-SUM" || input == "AGG-PRO" ||
		input == "AGG-AVG" || input == "AGG-FST" ||
		input == "AGG-LST" || input == "SRT-REV" ||
		input == "SRT-ORD" || input == "SRT-SLC" ||
		input == "SRT-DST" || input == "/MAP-INC" ||
		input == "/MAP-MLT" || input == "/AGG-SUM" ||
		input == "/AGG-PRO" || input == "/AGG-AVG" ||
		input == "/AGG-FST" || input == "/AGG-LST" ||
		input == "/SRT-REV" || input == "/SRT-ORD" ||
		input == "/SRT-SLC" || input == "/SRT-DST";
}

bool isMissingDash(std::string &input)
{
	return input == "MAPINC" || input == "MAPMLT" ||
		input == "AGGSUM" || input == "AGGPRO" ||
		input == "AGGAVG" || input == "AGGFST" ||
		input == "AGGLST" || input == "SRTREV" ||
		input == "SRTORD" || input == "SRTSLC" ||
		input == "SRTDST" || input == "/MAPINC" ||
		input == "/MAPMLT" || input == "/AGGSUM" ||
		input == "/AGGPRO" || input == "/AGGAVG" ||
		input == "/AGGFST" || input == "/AGGLST" ||
		input == "/SRTREV" || input == "/SRTORD" ||
		input == "/SRTSLC" || input == "/SRTDST";
}

bool hasValueDash(std::string &input)
{
	return input == "MAP-INC" || input == "MAP-MLT" || input == "SRT-ORD" || input == "SRT-SLC";
}

bool hasValueNoDash(std::string &input)
{
	return input == "MAPINC" || input == "MAPMLT" || input == "SRTORD" || input == "SRTSLC";
}

bool hasNoValue(std::string &input)
{
	return input == "AGG-SUM" || input == "AGG-PRO" ||
		input == "AGG-AVG" || input == "AGG-FST" ||
		input == "AGG-LST" || input == "SRT-REV" ||
		input == "SRT-DST" || input == "/AGG-SUM" ||
		input == "/AGG-PRO" || input == "/AGG-AVG" ||
		input == "/AGG-FST" || input == "/AGG-LST" ||
		input == "/SRT-REV" || input == "/SRT-DST" ||
		input == "AGGSUM" || input == "AGGPRO" ||
		input == "AGGAVG" || input == "AGGFST" ||
		input == "AGGLST" || input == "SRTREV" ||
		input == "SRTDST" || input == "/AGGSUM" ||
		input == "/AGGPRO" || input == "/AGGAVG" ||
		input == "/AGGFST" || input == "/AGGLST" ||
		input == "/SRTREV" || input == "/SRTDST";
}