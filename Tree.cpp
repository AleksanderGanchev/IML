#include "Tree.h"

void Tree::copy(const Tree &other)
{
	setCurrentTag(other.currentTag);
	setLeft(other.left);
	setRight(other.right);
}

void Tree::destroy()
{
	delete[] this->currentTag;
	delete[] this->left;
	delete[] this->right;
}

Tree::Tree() : Tree(nullptr, nullptr, nullptr){}

Tree::Tree(const Tree &other)
{
	this->copy(other);
}

Tree::Tree(Tag *_currentTag, Tree *_left, Tree *_right) : currentTag(nullptr), left(nullptr), right(nullptr)
{
	this->currentTag = _currentTag;
	this->left = _left;
	this->right = _right;
}

Tree & Tree::operator=(const Tree &other)
{
	if (this != &other)
	{
		this->copy(other);
	}

	return *this;
}

Tree::~Tree()
{
	if (this == nullptr)
	{
		return;
	}

	if (this->left == nullptr && this->right == nullptr)
	{
		assert(this != nullptr);
		this->destroy();
		return;
	}

	this->left->~Tree();
	this->right->~Tree();
}

void Tree::setCurrentTag(Tag *newCurrentTag)
{
	if (this->currentTag != nullptr)
	{
		delete[] this->currentTag;
		this->currentTag = newCurrentTag;
	}
}

const Tag * Tree::getCurrentTag() const
{
	return this->currentTag;
}

void Tree::setLeft(Tree *newLeft)
{
	if (this->left != nullptr)
	{
		delete[] this->left;
		this->left = newLeft;
	}
}

const Tree * Tree::getLeft() const
{
	return this->left;
}

void Tree::setRight(Tree *newRight)
{
	if (this->right != nullptr)
	{
		delete[] this->right;
		this->right = newRight;
	}
}

const Tree * Tree::getRight() const
{
	return this->right;
}

size_t Tree::numberOfCoppies(Tree *current, Tree *toMatch)
{
	if (current == nullptr)
	{
		return 0;
	}

	if (current->currentTag->returnName() == toMatch->currentTag->returnName()) // compares the name of two nodes
	{
		return 1 + numberOfCoppies(current->left, toMatch) + numberOfCoppies(current->right, toMatch);
	}

	return 0 + numberOfCoppies(current->left, toMatch) + numberOfCoppies(current->right, toMatch);
}

void Tree::createTag(Tree *&currentNode, std::string &input, size_t &index, std::string &identificator)
{
	std::vector<double> emptyVector;
	std::string tagName;

	while (input[index] != '>') // sets tag name
	{
		tagName += input[index];
		index++;
	}

	tagName += input[index]; // adds '>' to the tag name
	index++;

	assert(currentNode == nullptr);

	if (tagName[1] == 'M')
	{
		currentNode = new Tree( new MapTag(tagName, emptyVector, identificator), nullptr, nullptr );
	}
	else if (tagName[1] == 'A')
	{
		currentNode = new Tree( new AggTag(tagName, emptyVector, identificator), nullptr, nullptr );
	}
	else if (tagName[1] == 'S')
	{
		currentNode = new Tree( new SrtTag(tagName, emptyVector, identificator), nullptr, nullptr );
	}
}

void Tree::addNumberToContent(Tree *&currentNode, std::string &input, size_t &index)
{
	std::string number;

	while (input[index] != ' ' && input[index] != '<') // saves all digits in the string
	{
		number += input[index];
		index++;
	}

	assert(number != " ");

	double numberToAdd = atof(number.c_str());
	currentNode->currentTag->addToContent(numberToAdd); // adds the number to current node's content
}

void Tree::moveIndex(Tree *startingNode, Tree *endNode, std::string &input, size_t &index)
{
	int nodeCoppiesCounter = numberOfCoppies(startingNode, endNode) - 1; // number of tags with the same name
	std::string nodeNameToMatch = endNode->currentTag->returnName();

	while (!(input[index] == '/' && input[index + 1] == nodeNameToMatch[1] && nodeCoppiesCounter == 0)) // moves index to closing tag
	{
		if (input[index] == '/' && input[index + 1] == nodeNameToMatch[1] && nodeCoppiesCounter != 0)
		{
			nodeCoppiesCounter--;
		}

		index++;
	}

	while (input[index] != '>')
	{
		index++;
	}
}

void Tree::executeEqualLvl(Tree *&currentNode, std::string &input, size_t &index, std::string &identificator) // creates left subtree to the farthest left node
{
	Tree *tempNode = farthestLeft(currentNode->right);

	assert(tempNode->left == nullptr);
	tempNode->left = createTree(tempNode->left, input, index, currentNode->currentTag->returnId() + "L");

	moveIndex(tempNode->left, tempNode->left, input, index);
}

void Tree::executeNesting(Tree *&currentNode, std::string &input, size_t &index, std::string &identificator) // creates right subtree
{
	assert(currentNode->right == nullptr);
	currentNode->right = createTree(currentNode->right, input, index, identificator + "R");

	Tree *tempNode = farthestLeft(currentNode->right);

	moveIndex(currentNode->right, tempNode, input, index);//move index to farthest left in the rigt subtree,because it's index will be farthest
}

Tree * Tree::farthestLeft(Tree *current)
{
	while (current->left != nullptr)
	{
		current = current->left;
	}

	return current;
}

Tree * Tree::createTree(Tree *&currentNode, std::string &input, size_t index, std::string identificator)
{
	std::vector<double> currentContent;

	createTag(currentNode, input, index, identificator);

	while (input[index] != '\0') // loops runs until the end of the text
	{
		if (isdigit(input[index]) == 4 || input[index] == '-') 
		{
			addNumberToContent(currentNode, input, index); // adds number to the current content
		}
		if (input[index] == '<')
		{
			if (input[index + 1] == '/')
			{
				while (input[index] != '>')
				{
					index++;
				}

				if (input[index + 1] == '<' && input[index + 2] != '/')
				{
					currentNode->left = createTree(currentNode->left, input, index + 1, identificator + "L"); // creates left subtree
					return currentNode;
				}
				else
				{
					return currentNode;
				}

			}
			else if (currentNode->right != nullptr)
			{
				executeEqualLvl(currentNode, input, index, identificator); // catch equal lvl implementation tags
			}
			else if (input[index] != '>')
			{
				executeNesting(currentNode, input, index, identificator); // catch nested tag
			}
		}
		index++;
	}

	return currentNode;
}

void Tree::print() // prints tree
{
	if (this == nullptr) 
	{
		return;
	}

	this->currentTag->printInformation();

	if (this->left == nullptr && this->right == nullptr)
	{
		return;
	}

	std::cout << "\n" << "(L:";
	if (this->left == nullptr)
	{
		std::cout << "EMPTY ";
	}

	this->left->print();

	std::cout << "\n\t" << "R:";
	if (this->right == nullptr)
	{
		std::cout << "EMPTY";
	}

	this->right->print();
	std::cout << ")";
}

void Tree::reverseTreeContent() // reverse every node's content
{
	if (this == nullptr)
	{
		return;
	}

	this->currentTag->reverseContent();

	this->left->reverseTreeContent();
	this->right->reverseTreeContent();
}

size_t Tree::numberOfDuplicates(Tree *first, Tree *current)
{
	if (first == nullptr || current == nullptr || first->currentTag->returnId() == current->currentTag->returnId())
	{
		return 0;
	}

	if (first->currentTag->returnName() == current->currentTag->returnName() && first->currentTag->returnContent() == current->currentTag->returnContent()) // case if the current tag's name is the same as the one to compare; processing all cases
	{
		if (first->right == nullptr && first->left == nullptr)
		{
			return 1;
		}

		return 1 + numberOfDuplicates(first->right, current) + numberOfDuplicates(first->left, current);
	}

	if (first->right == nullptr && first->left == nullptr)
	{
		return 0;
	}
	
	return 0 + numberOfDuplicates(first->right, current) + numberOfDuplicates(first->left, current);
}

void Tree::moveIndexAcrossTag(std::string &tempName, size_t &index, std::string &input)
{
	while (input[index] != '>')
	{
		tempName += input[index];
		index++;
	}

	tempName += input[index];
}

void Tree::addNumberFromText(std::vector<double> &result, size_t &index, std::string &input)
{
	std::string number;
	double tempNumber;

	while (input[index] != ' ' && input[index] != '<')
	{
		number += input[index];
		index++;
	}

	assert(number != " ");

	tempNumber = atof(number.c_str()); 
	result.push_back(tempNumber);
}

void Tree::calculateNesting(Tree *first, Tree *current, std::string &input, std::vector<double> &containerForCurrentContent, std::vector<double> &rightSubtreeResult)
{
	std::vector<double> tempContent;
	std::vector<double> resultGetNumbers = getDataInTag(first, current, input); // takes the numbers before the next tag

	while (!(containerForCurrentContent.empty()))
	{
		if (!(resultGetNumbers.empty())) 
		{
			tempContent.push_back(containerForCurrentContent.back());
			containerForCurrentContent.pop_back();
			resultGetNumbers.pop_back();
		}
		else if (rightSubtreeResult.empty())
		{
			tempContent.push_back(containerForCurrentContent.back());
			containerForCurrentContent.pop_back();
		}

		if (resultGetNumbers.empty())
		{
			if (current->right != nullptr)
			{
				if (current->right->left != nullptr && current->right->left->right == nullptr)
				{
					equalLvlNesting(first, current, input, containerForCurrentContent, rightSubtreeResult, tempContent); // catch equal level of implementation
				}
				else
				{
					transferContent(rightSubtreeResult, tempContent); // tranfer right subtree content to tempContent
				}
			}
			else
			{
				transferContent(rightSubtreeResult, tempContent);
			}
		}
	}

	transferContent(tempContent, containerForCurrentContent);
	reverseVector(containerForCurrentContent);
}

void Tree::equalLvlNesting(Tree *first, Tree *current, std::string &input, std::vector<double> &containerForCurrentContent, std::vector<double> &rightSubtreeResult, std::vector<double> &tempContent)
{
	Tree *tempNode = current->right;

	while (tempNode->left != nullptr) // loops until the furthest left node is reached
	{
		std::vector<double> leftSubtreeResult = returnTreeResult(first, tempNode->left, input);

		if (rightSubtreeResult.back() == leftSubtreeResult.back()) // checks if the current number is from the left subtree
		{
			std::vector<double> afterTag = getDataAfterTag(first, tempNode, input); // the numbers after the nested tag
			reverseVector(afterTag);

			while (!(afterTag.empty()))
			{
				tempContent.push_back(afterTag.back());
				afterTag.pop_back();
				containerForCurrentContent.pop_back();
			}

			tempContent.push_back(rightSubtreeResult.back());
			rightSubtreeResult.pop_back();

			tempNode = tempNode->left;
		}
		else
		{
			tempContent.push_back(rightSubtreeResult.back());
			rightSubtreeResult.pop_back();
		}
	}
}

void Tree::addNumbersBeforeTag(std::vector<double> &result, std::string &input, size_t &index)
{
	while (input[index] != '<' && input[index] != '\0')
	{
		if (isdigit(input[index]) == 4 || input[index] == '-')
		{
			addNumberFromText(result, index, input);
		}
		else
		{
			index++;
		}
	}
}

void Tree::transferContent(std::vector<double> &from, std::vector<double> &to)
{
	while (!(from.empty()))
	{
		to.push_back(from.back());
		from.pop_back();
	}
}

void Tree::calculateLeftSubtree(Tree *first, Tree *current, std::string &input, std::vector<double> &result, std::vector<double> &containerForCurrentContent)
{
	std::vector<double> leftSubtreeResult = returnTreeResult(first, current->left, input);

	result = returnNodeResult(current, containerForCurrentContent); 
	transferContent(leftSubtreeResult, result); // adds left subtree's result to current node's result
}

bool Tree::isCorrectContent(Tree *current, std::vector<double> result) // compares to vectors to each other 
{
	std::vector<double> tempResult = returnReversedVector(result);
	std::vector<double> tempContent = current->currentTag->returnContent();

	while (!(tempResult.empty()))
	{
		if (tempResult.back() != tempContent.back()) 
		{
			return false;
		}

		tempResult.pop_back();
		tempContent.pop_back();
	}

	return true;
}

std::vector<double> Tree::getDataAfterTag(Tree *first, Tree *current, std::string &input) 
{
	std::vector<double> result;
	size_t index = 0;
	size_t duplicates = numberOfDuplicates(first, current);

	while (input[index] != '\0')
	{
		std::string tempNodeName;

		if (input[index] == '<' && input[index + 1] != '/')
		{
			moveIndexAcrossTag(tempNodeName, index, input); // moves index until the end of the tag
		}

		if (tempNodeName == current->currentTag->returnName())
		{
			if (duplicates == 0)
			{
				addNumbersBeforeTag(result, input, index); // adds content before new tag and if it is not correct empties it

				if (isCorrectContent(current, result))
				{
					emptyVector(result); // empty the result, so we can save the numbers from the text in it
					index++;

					while (input[index] != '<' && input[index] != '\0')
					{
						if (isdigit(input[index]) == 4 || (input[index] == '-' && isdigit(input[index + 1]) == 4))
						{
							addNumberFromText(result, index, input);
						}
						else
						{
							index++;
						}
					}

					return result; // return result
				}

				emptyVector(result);
			}
			else
			{
				duplicates--;
			}
		}

		index++;
	}

	return result;
}

std::vector<double> Tree::getDataInTag(Tree *first, Tree *current, std::string &input)
{
	std::vector<double> result;
	size_t index = 0;
	size_t duplicates = numberOfDuplicates(first, current); // number of nodes with the same name and content

	while (input[index] != '\0')
	{
		std::string tempNodeName;

		if (input[index] == '<')
		{
			moveIndexAcrossTag(tempNodeName, index, input);
		}

		if (tempNodeName == current->currentTag->returnName()) 
		{
			if (duplicates == 0)
			{
				index++;
				addNumbersBeforeTag(result, input, index); // adds the number before a new tag

				if (isCorrectContent(current, result) == true) // if the content matches
				{
					return result;
				}
				else
				{
					emptyVector(result);
				}
			}
			else
			{
				duplicates--;
			}
		}
		index++;
	}

	return result;
}

std::vector<double> Tree::returnNodeResult(Tree *current, std::vector<double> &containerForCurrentContent)
{
	return current->currentTag->calculateNode(containerForCurrentContent); // return node result
}

std::vector<double> Tree::returnTreeResult(Tree *first, Tree *current, std::string &input)
{
	std::vector<double> containerForCurrentContent;
	std::vector<double> result;

	if (current == nullptr) // bottom
	{
		return result;
	}

	if (current->left == nullptr && current->right == nullptr) // case if the node is a leaf
	{
		containerForCurrentContent = current->currentTag->returnContent();
		result = returnNodeResult(current, containerForCurrentContent);

		return result;
	}

	std::vector<double> rightSubtreeResult = returnTreeResult(first, current->right, input);

	if ((!(getDataInTag(first, current, input).empty())) || (getDataInTag(first, current, input).empty() && (!(current->currentTag->returnContent().empty()))))
	{ // if there are numbers before the new tag in the text or there are no numbers before the new tag, but there are numbers in the tag's content
		containerForCurrentContent = current->currentTag->returnContent();
		calculateNesting(first, current, input, containerForCurrentContent, rightSubtreeResult);
	}
	else
	{
		reverseVector(containerForCurrentContent);
		transferContent(rightSubtreeResult, containerForCurrentContent); 
	}

	calculateLeftSubtree(first, current, input, result, containerForCurrentContent);
	reverseVector(result);

	return result;
}
