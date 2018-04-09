// x00111602
// Conor Griffin
#pragma once
#include <iostream>
#include <string> 
using namespace std;

class HuffNode
{
	friend class HuffTree;
public:
	HuffNode();
	HuffNode(char, int);
	~HuffNode();

	int getFrequency() {
		return frequency;
	}

private:
	char letter;
	string code;
	int frequency;
	HuffNode *leftChild, *rightChild;
};


