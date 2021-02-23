#pragma once
#include "MapTag.h"
#include "AggTag.h"
#include "SrtTag.h"

class Tree
{
private:
	Tag *currentTag;
	Tree *left;
	Tree *right;

	void copy(const Tree&);
	void destroy();

public:
	Tree();
	Tree(const Tree&);
	Tree(Tag*, Tree*, Tree*);
	Tree& operator=(const Tree&);
	~Tree();

	void setCurrentTag(Tag*);
	const Tag* getCurrentTag() const;

	void setLeft(Tree*);
	const Tree* getLeft() const;

	void setRight(Tree*);
	const Tree* getRight() const;

	size_t numberOfCoppies(Tree*, Tree*); // returns the number of nodes with the same tag name

	void createTag(Tree*&, std::string&, size_t&, std::string&); // creates a new tag in the memory
	void addNumberToContent(Tree*&, std::string&, size_t&); // adds a number to the current tag content
	void moveIndex(Tree*, Tree*, std::string&, size_t&); // moves index until end of tag
	void executeEqualLvl(Tree*&, std::string&, size_t&, std::string&); // creates left subtree 
	void executeNesting(Tree*&, std::string&, size_t&, std::string&); // creates right subtree

	Tree *farthestLeft(Tree*); // return the last left node in left subtree
	Tree *createTree(Tree*&, std::string&, size_t, std::string); // creates new node

	void print(); // prints tree
	void reverseTreeContent(); // reverses every node's content in the tree

	size_t numberOfDuplicates(Tree*, Tree*); // returns the number of nodes with the same name and content until the tag with the same id is reached

	void moveIndexAcrossTag(std::string&, size_t&, std::string&); // moves index till the end of the tag
	void addNumberFromText(std::vector<double>&, size_t&, std::string&); // adds number to current tag's content from text
	void calculateNesting(Tree*, Tree*, std::string&, std::vector<double>&, std::vector<double>&); // calculates right subtree result
	void equalLvlNesting(Tree*, Tree*, std::string&, std::vector<double>&, std::vector<double>&, std::vector<double>&); // calculate equal lvl implementation result
	void addNumbersBeforeTag(std::vector<double>&, std::string&, size_t&); // adds all the numbers before a new tag begins
	void transferContent(std::vector<double>&, std::vector<double>&); // transfer content between vectors
	void calculateLeftSubtree(Tree*, Tree*, std::string&, std::vector<double>&, std::vector<double>&); // calculate left subtree

	bool isCorrectContent(Tree*, std::vector<double>); // compares node's content to vector content

	std::vector<double> getDataAfterTag(Tree*, Tree*, std::string&); // returns all numbers after the current tag
	std::vector<double> getDataInTag(Tree*, Tree*, std::string&); // return numbers in the current tag

	std::vector<double> returnNodeResult(Tree*, std::vector<double>&); // return current node's result
	std::vector<double> returnTreeResult(Tree*, Tree*, std::string&); // return tree's result
};

