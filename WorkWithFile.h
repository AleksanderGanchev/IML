#pragma once
#include "ErrorList.h"
#include "Tree.h"

void printIntroduction() // prints information box 
{
	std::cout << "+------------------------WELCOME TO IML PARSER------------------------+" << std::endl;
	std::cout << "| IML Parser is a piece of software that reads IML scripts and returns|" << std::endl;
	std::cout << "| their result in a text-based file. It is capable of detecting more  |" << std::endl;
	std::cout << "| than 25 types of IML errors!                                        |" << std::endl;
	std::cout << "+---------------------------------------------------------------------+\n" << std::endl;
}

void saveInFile(std::string &output) // sets output file
{
	ErrorList saveErrors;
	std::string fileName;

	std::cout << "Enter the file in which you would like to save the result: ";
	std::cin >> fileName;

	std::ifstream outputFile(fileName);

	saveErrors.saveResult(outputFile, fileName, output); // checks for errors with saving the result
}

void printTreeResult(std::string &fileContent) // creates and calculutes tree
{
	Tree* tree = nullptr;

	tree->createTree(tree, fileContent, 0, "");
	tree->reverseTreeContent();

	std::vector<double> treeResult = tree->returnTreeResult(tree, tree, fileContent);
	std::string treeOutput = convertToString(treeResult);
	
	saveInFile(treeOutput); 
	tree->~Tree(); 
}

void openFile() // gets file scipt
{
	ErrorList errors;
	std::string fileName;

	std::cout << "Enter file name:";
	std::cin >> fileName;

	std::ifstream fileToRead(fileName);
	
	if (errors.fileValidation(fileToRead))
	{
		std::string fileContent;
		returnContent(fileToRead, fileContent);

		if (errors.scanForErrors(fileContent))
		{
			std::cout << "\nSTATUS: No errors were found!\n" << std::endl;
			printTreeResult(fileContent);
		}
	}
}